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
#include "heatmap.h"

#define __unused __attribute__((unused))

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

#define ROUND_DOWN(x, m) ((x) & ~((m) - 1))
#define ROUND_UP(x, m) (((x) + (m) - 1) & ~((m) - 1))

#define stdio_log(fmt...) do { \
		fprintf(stdout, fmt); \
	} while (0)
/* journalctl */
#define ldebug(fmt...) do { \
		if (!debug) \
			break; \
		stdio_log(fmt); \
		syslog(LOG_DEBUG, fmt); \
	} while (0)
#define linfo(fmt...) do { \
		stdio_log(fmt); \
		syslog(LOG_INFO, fmt); \
	} while (0)
#define lwarning(fmt...) do { \
		stdio_log(fmt); \
		syslog(LOG_WARNING, fmt); \
	} while (0)
#define lerror(fmt...) do { \
		stdio_log(fmt); \
		syslog(LOG_ERR, fmt); \
	} while (0)

static const char *const ANSI_COLORS_GRAY[] = {
	"\033[48;5;255m",
	"\033[48;5;252m",
	"\033[48;5;250m",
	"\033[48;5;248m",
	"\033[48;5;246m",
	"\033[48;5;244m",
	"\033[48;5;242m",
	"\033[48;5;240m",
	"\033[48;5;238m",
	"\033[48;5;236m",
	"\033[48;5;234m",
	"\033[48;5;232m",
};
static const char *const ANSI_COLORS_RESET = "\033[0m";
#define NR_ANSI ARRAY_SIZE(ANSI_COLORS_GRAY)

static const char __attribute__((unused)) * ansi_text[] = {
	" ", " ", ".", ".", "*", "*", "o", "o", "O", "O", "#", "#",
};

bool debug = false;

struct addr_node {
	/* [start, end) */
	unsigned long start, end;

	/* temp to use */
	unsigned long addr;

	unsigned long quota;

	rb_node(struct addr_node) rb_link_node;
};

typedef rb_tree(struct addr_node) addr_tree;

struct heatmap_space {
	addr_tree tree;

	/* bytes */
	unsigned long granularity;
	unsigned long max_addr, min_addr;
	unsigned long max_quota, min_quota;
};

rb_proto(static __unused, addr_, addr_tree, struct addr_node);

static int __addr_in_node(const struct addr_node *node, unsigned long addr)
{
	if (addr < node->start)
		return 1;
	else if (addr >= node->start && addr < node->end)
		return 0;
	else if (addr >= node->end)
		return -1;

	return 0;
}

static int addr_node_cmp(const struct addr_node *a, const struct addr_node *b)
{
	if (a->addr)
		return __addr_in_node(b, a->addr);

	if (b->addr)
		return __addr_in_node(a, b->addr);

	if (b->end <= a->start)
		return -1;
	else if (a->start < b->end && a->end > b->start)
		return 0;
	else if (a->end <= b->start)
		return 1;

	return 0;
}

rb_gen(static __unused, addr_, addr_tree, struct addr_node, rb_link_node,
       addr_node_cmp);

struct addr_node *get_addr_node(addr_tree *tree, unsigned long addr);

int heatmap_create_space(struct heatmap_space **space,
			 unsigned long granularity)
{
	struct heatmap_space *new = malloc(sizeof(struct heatmap_space));
	memset(new, 0, sizeof(struct heatmap_space));

	addr_new(&new->tree);

	new->granularity = power_of_2(granularity);
	new->min_addr = -1UL;
	new->max_addr = 0;
	new->min_quota = -1UL;
	new->max_quota = 0;

	*space = new;

	return 0;
}

int heatmap_insert_addr(struct heatmap_space *space, unsigned long addr,
			unsigned long quota)
{
	struct addr_node *new = NULL;

	if (addr == 0 || quota == 0)
		return -EINVAL;

	if (heatmap_has_addr(space, addr)) {
		new = get_addr_node(&space->tree, addr);
		new->quota += quota;
		ldebug("Update %#016lx %ld\n", new->start, new->quota);
		return 0;
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

	return 0;
}

static void print_range(struct heatmap_space *space, FILE *fp)
{
	FILE *std = fp ?: stdout;

	fprintf(std, "Address Range: %#016lx - %#016lx.\n",
		space->min_addr, space->max_addr);
	fprintf(std, "Quota Range: %ld - %ld.\n",
		space->min_quota, space->max_quota);
	fprintf(std, "Granularity: %#016lx\n", space->granularity);
}

void heatmap_print_space(struct heatmap_space *space, FILE *fp)
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

void heatmap_quota_normalization(struct heatmap_space *space, unsigned long min,
				 unsigned long max)
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

void heatmap_addr_normalization(struct heatmap_space *space, unsigned long min,
				unsigned long max)
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

bool heatmap_has_addr(struct heatmap_space *space, unsigned long addr)
{
	return get_addr_node(&space->tree, addr) ? true : false;
}

void heatmap_plot_space(FILE *fp, struct heatmap_space *space,
			unsigned long col, const char *f_bin, bool text_only)
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
	fprintf(std, "  %16s [[Address vs. Quota logf() plot]]\n", "");
	fprintf(std, "\n");
	fprintf(std, "  %16s |<----->| = %#0lx bytes\n", "",
		8 * space->granularity);
	fprintf(std, "  %16s ", "");
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
			fprintf(std, "%#018lx ", addr);
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

void heatmap_print_ansis(void)
{
	int i;
	for (i = 0; i < NR_ANSI; i++)
		printf("%4d %s   %s\n", i, ANSI_COLORS_GRAY[i],
		       ANSI_COLORS_RESET);
}
