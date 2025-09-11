#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/inotify.h>
#include <signal.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <assert.h>

#include <addr.h>
#include <common.h>


struct addr_node *get_addr_node(addr_tree *tree, unsigned long addr);

void init_addr_space(struct addr_space *space, unsigned long granularity)
{
	memset(space, 0, sizeof(struct addr_space));

	addr_new(&space->tree);

	space->granularity = power_of_2(granularity);
	space->min_addr = -1UL;
	space->max_addr = 0;
	space->min_quota = -1UL;
	space->max_quota = 0;
}

void insert_addr(struct addr_space *space, unsigned long addr, unsigned long quota)
{
	struct addr_node *new = NULL;

	if (addr == 0)
		return;

	if (has_addr(space, addr)) {
		new = get_addr_node(&space->tree, addr);
		new->quota += quota;
		ldebug("Update %#016lx %ld\n", new->start, new->quota);
		return;
	}

	new = malloc(sizeof(struct addr_node));

	memset(new, 0, sizeof(struct addr_node));

	new->start = ROUND_DOWN(addr, space->granularity);
	new->end = ROUND_UP(addr, space->granularity);
	new->quota = quota;

	if (new->start == new->end)
		new->end = ROUND_UP(addr + 1, space->granularity);

	if (space->min_addr > new->start)
		space->min_addr = new->start;
	if (space->max_addr < new->end)
		space->max_addr = new->end;

	ldebug("Insert %#016lx %ld\n", addr, quota);

	addr_insert(&space->tree, new);
}

static void print_range(struct addr_space *space, FILE *fp)
{
	FILE *std = fp ?: stdout;

	fprintf(std, "Address Range: %#016lx - %#016lx.\n",
		space->min_addr, space->max_addr);
	fprintf(std, "Quota Range: %ld - %ld.\n",
		space->min_quota, space->max_quota);
	fprintf(std, "Granularity: %#016lx\n", space->granularity);
}

void print_addr_space(struct addr_space *space, FILE *fp)
{
	struct addr_node *a = NULL;
	FILE *std = fp ?: stdout;

	fprintf(std, "=======\n");
	print_range(space, std);
	for (a = addr_first(&space->tree); a; a = addr_next(&space->tree, a)) {
		fprintf(std, "%#016lx - %#016lx %ld\n",
			a->start, a->end, a->quota);
	}
}

static bool
addr_in_range(unsigned long addr, unsigned long start, unsigned long end)
{
	if (addr >= start && addr < end)
		return true;

	return false;
}

void quota_normalization(struct addr_space *space,
		unsigned long min, unsigned long max)
{
	struct addr_node *a = NULL;

	space->min_quota = -1UL;
	space->max_quota = 0;

	for (a = addr_first(&space->tree); a; a = addr_next(&space->tree, a)) {

		if (min < max) {
			if (!addr_in_range(a->start, min, max) &&
				!addr_in_range(a->end - 1, min, max))
				continue;
		}

		if (space->min_quota > a->quota)
			space->min_quota = a->quota;
		if (space->max_quota < a->quota)
			space->max_quota = a->quota;
	}
}

void addr_normalization(struct addr_space *space,
		unsigned long min, unsigned long max)
{
	if (min)
		space->min_addr = min;
	if (max)
		space->max_addr = max;

#if 0
	struct addr_node *a = NULL;

	for (a = addr_first(&space->tree); a; a = addr_next(&space->tree, a)) {

		if (space->min_addr > a->start)
			space->min_addr = a->start;
		if (space->max_addr < a->end)
			space->max_addr = a->end;
	}
#endif
}

struct addr_node *get_addr_node(addr_tree *tree, unsigned long addr)
{
	struct addr_node node = {
		.addr = addr,
	};

	return addr_search(tree, &node);
}

bool has_addr(struct addr_space *space, unsigned long addr)
{
	return get_addr_node(&space->tree, addr) ? true : false;
}

void plot_space(FILE *fp, struct addr_space *space, unsigned long col,
		const char *f_bin, bool text_only)
{
	unsigned long addr;
	struct addr_node *node;
	unsigned long quota;
	unsigned int ansi_idx = 0;
	unsigned int ansi_num = NR_ANSI;
	FILE *std = fp ?: stdout;
	unsigned int icol, igran;

	FILE *fp_bin = NULL;

	if (f_bin)
		fp_bin = fopen(f_bin, "w");


	/* | | | */
	fprintf(std, "%16s [[Address vs. Quota logf() plot]]\n", "");
	fprintf(std, "\n");
	fprintf(std, "%16s |<----->| = %#0lx bytes\n", "", 8 * space->granularity);
	fprintf(std, "%16s ", "");
	for (icol = 0, igran = 0; icol <= col;
		igran += space->granularity, icol++) {

		if (icol % 8 == 0)
			fprintf(std, "|");
		else
			fprintf(std, " ");
	}
	fprintf(std, "\n");

	for (icol = 1, addr = space->min_addr;
		addr <= space->max_addr;
		addr += space->granularity, icol++) {

		node = get_addr_node(&space->tree, addr);

		if (node) {
			quota = node->quota;
		} else {
			quota = 0UL;
		}

		float quota_range = space->max_quota - space->min_quota;
		float quota_value = (quota - space->min_quota) * 1.0f;

		/* Zoom down, it's a good way to make the difference, otherwise you
		 * won't see the difference when you draw */
		quota_value = logf(quota_value);
		quota_range = logf(quota_range);

		float normalization_value = quota_value * ansi_num / quota_range;

		if (quota == 0)
			ansi_idx = 0;
		else
			ansi_idx = normalization_value;

		if (fp_bin)
			fwrite(&normalization_value, sizeof(float), 1, fp_bin);

		if (ansi_idx >= ansi_num) {
			ldebug("ANSI overflow: %d(%d)\n", ansi_idx, ansi_num);
			ansi_idx = ansi_num - 1;
		}

		if (icol % col == 1) {
			fprintf(std, "%#016lx ", addr);
		}

		if (text_only)
			fprintf(std, "%s", ansi_text[ansi_idx]);
		else
			fprintf(std, "%s %s", ANSI_COLORS_GRAY[ansi_idx], ANSI_COLORS_RESET);

		if (icol % col == 0) {
			fprintf(std, "\n");
		}
	}

	fprintf(std, "\n");
	print_range(space, std);

	if (fp_bin)
		fclose(fp_bin);
}

unsigned long strtoaddr(const char *s)
{
	if (!s)
		return 0;

	if (s[0] == '0' && s[1] == 'x')
		return strtoul(s, NULL, 16);
	else
		return strtoul(s, NULL, 10);

	return 0;
}

