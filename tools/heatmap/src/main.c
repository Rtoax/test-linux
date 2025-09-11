/**
 * Memory Heat Map
 *
 * Copyright (C) CESTC, Co.
 *
 * 2023-04-06	Rong Tao	Create this.
 * 2023-05-29	Rong Tao	Add --gran-cl3 argument
 */
#include <stdio.h>
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
#include <time.h>

#include <addr.h>
#include <common.h>


static struct addr_space space;

static char *f_txt = NULL;
static char *f_output_bin = NULL;
static bool rand_seed = false;
static bool text_only = false;

static unsigned long default_granularity = 64;
static unsigned long default_col = 64;
static unsigned long default_min_addr = 0;
static unsigned long default_max_addr = 0;

void print_help(int _exit)
{
	linfo(
	"\n"
	"heatmap\n"
	"\n"
	" -i, --input     input data text file\n"
	"                 Format:\n"
	"                 [address] [quota|count]\n"
	"\n"
	" -o, --output    output binary file\n"
	"                 check with ximage, see [0]\n"
	"\n"
	" -r, --rand      use rand value\n"
	"\n"
	" --min-addr      only plot address range min\n"
	" --max-addr      only plot address range max\n"
	"\n"
	" --gran          set granularity, default: %ld bytes\n"
	" --gran-cl3      granularity equal to LEVEL3 cacheline size\n"
	" --col           set coloum, default: %ld num\n"
	"\n"
	" --debug         debug mode\n"
	" -h, --help      show this information\n"
	"\n"
	" --ansi          print ansi example\n"
	" --text-only     print text instead of ansi\n"
	"\n"
	"[0] https://github.com/JohnWStockwellJr/SeisUnix.git\n"
	"\n",
	default_granularity,
	default_col
	);
	exit(_exit);
}

enum {
	ARG_DEBUG = 200,
	ARG_GRAN,
	ARG_GRAN_CL3,
	ARG_PLOT_COL,
	ARG_MIN_ADDR,
	ARG_MAX_ADDR,
	ARG_ANSI_PRINT,
	ARG_TEXT_ONLY,
};

static int parse_args(int argc, char *argv[])
{
	struct option options[] = {
	{ "input",     required_argument, 0, 'i' },
	{ "rand",            no_argument, 0, 'r' },
	{ "min-addr",  required_argument, 0, ARG_MIN_ADDR },
	{ "max-addr",  required_argument, 0, ARG_MAX_ADDR },
	{ "gran",      required_argument, 0, ARG_GRAN },
	{ "gran-cl3",        no_argument, 0, ARG_GRAN_CL3 },
	{ "col",       required_argument, 0, ARG_PLOT_COL },
	{ "output",    required_argument, 0, 'o' },
	{ "debug",           no_argument, 0, ARG_DEBUG },
	{ "help",            no_argument, 0, 'h' },
	{ "ansi",            no_argument, 0, ARG_ANSI_PRINT },
	{ "text-only",       no_argument, 0, ARG_TEXT_ONLY },
	{ NULL },
	};

	while (1) {
		int opt_idx;
		int c = getopt_long(argc, argv, "i:o:rh", options, &opt_idx);
		if (c < 0)
			break;
		switch (c) {
		case 'i':
			f_txt = optarg;
			break;
		case 'o':
			f_output_bin = optarg;
			break;
		case 'r':
			rand_seed = true;
			break;
		case ARG_GRAN:
			default_granularity = power_of_2(strtoul(optarg, NULL, 10));
			break;
		case ARG_GRAN_CL3:
			default_granularity = sysconf(_SC_LEVEL3_CACHE_LINESIZE) / 8;
			break;
		case ARG_PLOT_COL:
			default_col = power_of_2(strtoul(optarg, NULL, 10));
			break;
		case ARG_MIN_ADDR:
			default_min_addr = strtoaddr(optarg);
			break;
		case ARG_MAX_ADDR:
			default_max_addr = strtoaddr(optarg);
			break;
		case ARG_DEBUG:
			debug = true;
			break;
		case 'h':
			print_help(0);
			break;
		case ARG_ANSI_PRINT:
			print_ansi();
			exit(0);
			break;
		case ARG_TEXT_ONLY:
			text_only = true;
			break;
		default:
			print_help(1);
			break;
		}
	}

	if (!rand_seed && !f_txt) {
		lerror("Must specify -i or -r\n");
		exit(1);
	}
	if (!rand_seed && f_txt && access(f_txt, F_OK) != 0) {
		lerror("TXT %s is not exist, see -i\n", f_txt);
		exit(1);
	}

	return 0;
}

void init_rand(void)
{
	unsigned long i;

	for (i = 0xffff0000; i < 0xffffffff; i += default_granularity) {
		unsigned long quota = random() % 1024;
		ldebug("quota %ld\n", quota);
		insert_addr(&space, i, quota);
	}
}

int load_count_txt(void)
{
	FILE *fp = fopen(f_txt, "r");
	char s_cnt[32], s_addr[256];
	unsigned long addr, quota;

	while (fscanf(fp, "%s %s", s_addr, s_cnt) != EOF) {
		ldebug("function count: %s %s\n", s_addr, s_cnt);

		if (s_addr[0] == '0' && s_addr[1] == 'x')
			addr = strtoul(s_addr, NULL, 16);
		else if (s_addr[0] == '0')
			addr = strtoul(s_addr, NULL, 8);
		else
			addr = strtoul(s_addr, NULL, 10);

		if (addr == 0)
			continue;

		quota = strtoul(s_cnt, NULL, 10);

		insert_addr(&space, addr, quota);
	}

	fclose(fp);

	return 0;
}

int main(int argc, char *argv[])
{
	parse_args(argc, argv);

	linfo("Starting...\n");
	srandom((int)time(0));

	init_addr_space(&space, default_granularity);

	if (rand_seed)
		init_rand();
	else
		load_count_txt();

	quota_normalization(&space, default_min_addr, default_max_addr);
	addr_normalization(&space, default_min_addr, default_max_addr);

//	print_addr_space(&space, NULL);

	plot_space(NULL, &space, default_col, f_output_bin, text_only);

	return 0;
}

