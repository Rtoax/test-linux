#include <assert.h>
#include <argp.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/time.h>

#include "oom_helpers.h"

volatile sig_atomic_t keep_going = 1;

size_t mem_size = 0;
enum {
	OP_GLIBC = 1,
	OP_MMAP_ANON,
	OP_MMAP_FILE,
} op_type = OP_GLIBC; /* default use glibc */
int oom_adj;
int oom_score_adj;
bool flag_popen =
#if !defined(POPEN)
	false;
#pragma message("without popen(3)")
#else
	true;
#pragma message("with popen(3)")
#endif
int verbose = false;
unsigned long rate_limit = 9999999999;

const char argp_prog_doc[] =
	"USAGE: [-p] [-s <size>] [-a <oom_adj>] [-c <oom_score_adj>] [-v|--verbose]\n"
	"\n"
	"EXAMPLES\n"
	"  $ ./oom -v -s 2GB --oom_score_adj -1000\n"
	"  $ ./oom -v\n"
	"  $ ./oom -v --rate 1000MB\n";

static const struct argp_option opts[] = {
	{ "operation", 'e', "OPERATION", 0, "specify operation, glibc, mmap-anon, mmap-file" },
	{ "size", 's', "SIZE", 0, "only allocate size of memory, instead of oom, suffix KB, MB, GB" },
	{ "rate", 'r', "RATE", 0, "limit the alloc rate, suffix KB, MB, GB" },
	{ "popen", 'p', NULL, 1, "test popen(3) after memory" },
	{ "verbose", 'v', NULL, 1, "display detail" },
	{ "oom_adj", 'a', "OOM_ADJ", 0, "set oom_adj (-17 to 15)" },
	{ "oom_score_adj", 'c', "OOM_SCORE_ADJ", 0, "set oom_score_adj (-1000 to 1000)" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'e':
		if (!strcmp(arg, "glibc"))
			op_type = OP_GLIBC;
		else if (!strcmp(arg, "mmap-anon"))
			op_type = OP_MMAP_ANON;
		else if (!strcmp(arg, "mmap-file"))
			op_type = OP_MMAP_FILE;
		else {
			fprintf(stderr, "ERROR: operation only glibc, mmap-anon, mmap-file");
			exit(EXIT_FAILURE);
		}
		break;
	case 's':
		mem_size = str2size(arg);
		break;
	case 'r':
		rate_limit = str2size(arg);
		break;
	case 'a':
		oom_adj = atoi(arg);
		break;
	case 'c':
		oom_score_adj = atoi(arg);
		break;
	case 'p':
		flag_popen = true;
		break;
	case 'v':
		verbose = true;
		break;
	case ARGP_KEY_ARG:
		argp_usage(state);
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static const struct argp argp = {
	.options = opts,
	.parser = parse_arg,
	.doc = argp_prog_doc,
};

void sig_handler(int signum)
{
	psignal(signum, "\n\nGet signal");

	switch (signum) {
	case SIGINT:
		keep_going = 0;
		break;
	}
}

unsigned long usecs(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000UL + tv.tv_usec;
}

static inline void backspace(FILE *fp, int n)
{
	char buf[256];
	memset(buf, '\b', n);
	buf[n] = '\0';
	fprintf(fp, "%s", buf);
}

#define BACK_PRINTF(fmt...) do {			\
		int ____n = fprintf(stderr, fmt);	\
		if (keep_going)				\
			backspace(stderr, ____n);	\
		else					\
			fprintf(stderr, "\n");		\
	} while (0)

struct oom_operations {
	const char *name;
	size_t total_size;
	void *(*alloc)(size_t size);
	void (*pagefault)(void *mem, size_t size, bool verbose);
	void (*free)(void *mem, size_t size);
};

void *glibc_alloc(size_t size)
{
	return malloc(size);
}

void glibc_free(void *mem, size_t size)
{
	free(mem);
}

void *mmap_anon_alloc(size_t size)
{
	return mmap(NULL, size, PROT_READ | PROT_WRITE,
		    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

void mmap_anon_free(void *mem, size_t size)
{
	munmap(mem, size);
}

void default_pagefault(void *mem, size_t size, bool verbose)
{
	size_t i;
	size_t pf_size = 0;
	const size_t pagesize = getpagesize();

	for (i = 0; i < size && keep_going; i += pagesize) {
		((char *)mem)[i] = 'a';

		pf_size += pagesize;
		if (verbose) {
			BACK_PRINTF("Pagefault %ld B (%ld KiB, %ld MiB), oom_score %d, score_adj %d",
					pf_size, pf_size / KB, pf_size / MB,
					get_oom_score(getpid()),
					get_oom_score_adj(getpid()));
		}
	}
}

struct oom_operations glibc_ops = {
	.name = "GLIBC",
	.total_size = 0,
	.alloc = glibc_alloc,
	.pagefault = default_pagefault,
	.free = glibc_free,
};

struct oom_operations mmap_anon_ops = {
	.name = "MMAP",
	.total_size = 0,
	.alloc = mmap_anon_alloc,
	.pagefault = default_pagefault,
	.free = mmap_anon_free,
};

int test_popen(void)
{
	char buf[128] = "uname -rm";
	FILE *fp = popen(buf, "r");

	if (fp == NULL) {
		fprintf(stderr, "popen(%s) %m\n", buf);
	}
#ifdef DEBUG
	char line[256] = {0};
	while (fgets(line, 256, fp))
		fprintf(stderr, "%s", line);
#endif
	pclose(fp);
	return 0;
}

void hold_mem(struct oom_operations *ops)
{
	size_t size;
	char *mem;

	size = ops->total_size;

	if (size >= totalram()) {
		if (size >= totalram() + totalswap()) {
			fprintf(stderr, "\033[31mERROR: alloc > ram + swap\033[m\n");
			exit(EXIT_FAILURE);
		}
		fprintf(stderr, "\033[31mWARNING: Trying to alloc memory size bigger than system RAM size. May use Swap\033[m\n");
	}

	fprintf(stderr, "Hold %ld B (%ldKiB, %ldMiB) of memory\n", size,
		size / 1024, size / 1024 / 1024);

	mem = ops->alloc(size);
	if (!mem) {
		fprintf(stderr, "malloc(%ld) = NULL, %m.\n", size);
		exit(EXIT_FAILURE);
	}

	while (keep_going) {
		ops->pagefault(mem, size, true);
		if (flag_popen)
			test_popen();
		sleep(1);
	}

	ops->free(mem, size);
}

void try_oom(struct oom_operations *ops)
{
	const size_t pagesize = getpagesize();
	const size_t blk = pagesize * 100;
	char *mem;
	size_t cal_rate_size = 0;
	double rate_Mps;
	unsigned long start, end;

	fprintf(stderr, "OOMing...\n");

	start = usecs();
	cal_rate_size = 0;

	while (keep_going) {
		end = usecs();

		/* calculate rate per second */
		if (end - start >= 1000000UL) {
			start = usecs();
			cal_rate_size = 0;
			rate_Mps = 0.0f;
		}

		/* No need to free(), just leak it. */
		mem = ops->alloc(blk);
		ops->pagefault(mem, blk, false);

		ops->total_size += blk;
		cal_rate_size += blk;

		rate_Mps = cal_rate_size * 1.0f / (usecs() - start);

		if (flag_popen)
			test_popen();

		if (verbose) {
			BACK_PRINTF("allocated %ld B (%ld MiB, %ld GiB), %.2lf MiB/s, oom_score %d, score_adj %d",
				    ops->total_size, ops->total_size / 1024 / 1024,
				    ops->total_size / 1024 / 1024 / 1024,
				    rate_Mps,
				    get_oom_score(getpid()),
				    get_oom_score_adj(getpid()));
		}
		/* Limit the allocate rate */
		if (rate_Mps > (rate_limit / 1024.0f / 1024.0f))
			usleep(5000);
	}

	/* No need to free??? */
}

int main(int argc, char *argv[])
{
	int err;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	signal(SIGINT, sig_handler);

	mlockall(MCL_CURRENT);

	if (oom_adj) {
		printf("set oom_adj to %d\n", oom_adj);
		err = set_oom_adj(getpid(), oom_adj);
		if (err != 0)
			return err;
	}

	if (oom_score_adj) {
		printf("set oom_score_adj to %d\n", oom_score_adj);
		err = set_oom_score_adj(getpid(), oom_score_adj);
		if (err != 0)
			return err;
	}

	if (verbose) {
		printf("pid %d\n", getpid());
		printf("oom_adj %d\n", get_oom_adj(getpid()));
		printf("oom_score_adj %d\n", get_oom_score_adj(getpid()));
		printf("oom_score %d\n", get_oom_score(getpid()));
	}

	struct oom_operations *ops;
	switch (op_type) {
	case OP_GLIBC:
		ops = &glibc_ops;
		break;
	case OP_MMAP_ANON:
		ops = &mmap_anon_ops;
		break;
	case OP_MMAP_FILE:
		fprintf(stderr, "ERROR: not support yet.\n");
		exit(EXIT_FAILURE);
		break;
	}

	if (verbose) {
		printf("Use OOM operator %s\n", ops->name);
	}

	if (mem_size) {
		ops->total_size = mem_size;
		hold_mem(ops);
	} else {
		try_oom(ops);
	}

	return 0;
}
