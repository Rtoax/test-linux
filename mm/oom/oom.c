/**
 * TODO: cgroup oom, tmpfs oom.
 */
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

size_t total_size = 0;
size_t mem_size = 0;
enum {
	OP_GLIBC = 1,
	OP_MMAP_ANON,
	OP_MMAP_FILE,
} op_type = OP_GLIBC;
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

const char argp_prog_doc[] =
	"USAGE: [-p] [-s <size>] [-a <oom_adj>] [-c <oom_score_adj>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "operation", 'e', "OPERATION", 0, "specify operation, glibc, mmap-anon, mmap-file" },
	{ "size", 's', "SIZE", 0, "only allocate size of memory, instead of oom" },
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
		mem_size = strtoul(arg, NULL, 10);
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
	psignal(signum, "\nGet signal");

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

void hold_mem(size_t size)
{
	size_t i;
	const int pagesize = getpagesize();
	char *mem;

	fprintf(stderr, "Hold %ld B (%ldMib) of memory\n", size,
		size / 1024 / 1024);

	mem = malloc(size);
	total_size = size;

	while (keep_going) {
		for (i = 0; i < size; i += pagesize)
			mem[i] = 'a';
		if (flag_popen)
			test_popen();
		sleep(1);
	}
}

struct oom_operations {
	void *(*alloc)(size_t size);
	void (*pagefault)(void *mem, size_t size);
};

void *glibc_alloc(size_t size)
{
	return malloc(size);
}

void *mmap_anon_alloc(size_t size)
{
	return mmap(NULL, size, PROT_READ | PROT_WRITE,
		    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

void default_pagefault(void *mem, size_t size)
{
	size_t i;
	const size_t pagesize = getpagesize();
	for (i = 0; i < size; i += pagesize)
		((char *)mem)[i] = 'a';
}

struct oom_operations glibc_ops = {
	.alloc = glibc_alloc,
	.pagefault = default_pagefault,
};

struct oom_operations mmap_anon_ops = {
	.alloc = mmap_anon_alloc,
	.pagefault = default_pagefault,
};

void try_oom(struct oom_operations *ops)
{
	int n;
	const size_t pagesize = getpagesize();
	const size_t blk = pagesize * 100;
	char *mem;
	size_t cal_rate_size = 0;
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
		}

		/* No need to free(), just leak it. */
		mem = ops->alloc(blk);
		ops->pagefault(mem, blk);

		total_size += blk;
		cal_rate_size += blk;

		if (flag_popen)
			test_popen();

		if (verbose) {
			n = fprintf(stderr, "allocated %ld B (%ld MiB, %ld GiB), %.2lf MiB/s, oom_score %d",
				    total_size, total_size / 1024 / 1024,
				    total_size / 1024 / 1024 / 1024,
				    cal_rate_size * 1.0 / (usecs() - start),
				    get_oom_score(getpid()));
			if (keep_going)
				backspace(stderr, n);
		}
	}
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
		printf("get oom_adj %d\n", get_oom_adj(getpid()));
		printf("get oom_score_adj %d\n", get_oom_score_adj(getpid()));
		printf("get oom_score %d\n", get_oom_score(getpid()));
	}

	if (mem_size)
		hold_mem(mem_size);
	else {
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
		try_oom(ops);
	}

	return 0;
}
