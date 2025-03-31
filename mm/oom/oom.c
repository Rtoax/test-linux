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
#include <sys/mman.h>

#include "helpers.h"

volatile sig_atomic_t keep_going = 1;

size_t mem_size = 0;
bool flag_oom_adj = false;
int oom_adj;
bool flag_oom_score_adj = false;
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
	{ "size", 's', "INTERFACE", 0, "only allocate size of memory, instead of oom" },
	{ "popen", 'p', "POPEN", 1, "test popen(3) after memory" },
	{ "verbose", 'v', "VERBOSE", 1, "display detail" },
	{ "oom_adj", 'a', "OOM_ADJ", 0, "set oom_adj" },
	{ "oom_score_adj", 'c', "OOM_SCORE_ADJ", 0, "set oom_score_adj" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 's':
		mem_size = strtoul(arg, NULL, 10);
		break;
	case 'a':
		flag_oom_adj = true;
		oom_adj = atoi(arg);
		break;
	case 'c':
		flag_oom_score_adj = true;
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

	if (verbose)
		fprintf(stderr, "Hold %ld B (%ldMib) of memory\n", size,
			size / 1024 / 1024);

	mem = malloc(size);

	while (keep_going) {
		for (i = 0; i < size; i += pagesize)
			mem[i] = 'a';
		if (flag_popen)
			test_popen();
		sleep(1);
	}
}

void try_oom(void)
{
	int i, n;
	const size_t pagesize = getpagesize();
	const size_t blk = pagesize * 100;
	char *mem;
	size_t total_size = 0;

	if (verbose)
		fprintf(stderr, "OOMing...\n");

	while (keep_going) {
		mem = malloc(blk);
		for (i = 0; i < blk; i += pagesize)
			mem[i] = 'a';
		total_size += blk;
		if (flag_popen)
			test_popen();
		/* No need to free(), just leak it. */
		if (verbose) {
			n = fprintf(stderr, "allocated %ld B (%ld MiB, %ld GiB), oom_score %d",
				    total_size, total_size / 1024 / 1024,
				    total_size / 1024 / 1024 / 1024,
				    get_oom_score(getpid()));
			while (n--)
				fprintf(stderr, "\b");
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

	if (flag_oom_adj) {
		printf("set oom_adj to %d\n", oom_adj);
		err = set_oom_adj(getpid(), oom_adj);
		if (err != 0)
			return err;
	}

	if (flag_oom_score_adj) {
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
	else
		try_oom();

	return 0;
}
