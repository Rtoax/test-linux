// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2023-2025 Rong Tao. */
/**
 * cache-misses.c - Test the program efficiency problems caused by the
 * influence of data structures on cache misses.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

#define ARRAY_SIZE(arr) ((sizeof(arr)) / (sizeof(arr[0])))
#define LOOP	100000000L

enum op_type {
	OP_RD,
	OP_WR,
};

/**
 * Two threads accessing t1 and t2 at the same time (usually writes), this
 * access should be avoided, if it cannot be avoided, it should be ensured
 * that t1 and t2 are not in the same cache line, otherwise, when writing t1,
 * t2 and t1 are in a cache line, causing t2 to invalidate in the cache.
 */
struct good_struct {
	unsigned long t1;
#if defined(LEVEL3_CACHE_LINESIZE)
	char pad[LEVEL3_CACHE_LINESIZE];
#else
	/* Usually the LLC cache line size is 64 bytes */
	unsigned long pad[8];
#endif
	unsigned long t2;
};

/**
 * The two threads write t1 and t2, respectively, which causes cache
 * oscillation.
 */
struct bad_struct {
	unsigned long t1;
	unsigned long t2;
};

static unsigned long nloop = LOOP;

void show_diff_tv(const char *name, struct timeval *end, struct timeval *start)
{
	printf("%32s: %ld us\n",
		name,
		(end->tv_sec - start->tv_sec) * 1000000
		+ (end->tv_usec - start->tv_usec));
}

struct thread_arg {
	char *name;
	enum op_type op;
	unsigned long *pt;
};

static inline unsigned long long test_read(unsigned long *pt)
{
	unsigned long i;
	unsigned long long tmp = 0;
	for(i = 0; i < nloop; i++)
		tmp += *pt;
	return tmp;
}

static inline void test_write(unsigned long *pt)
{
	unsigned long i;
	for(i = 0; i < nloop; i++)
		*pt += 1;
}

void* thread_fn(void *arg)
{
	struct timeval tv1, tv2;
	struct thread_arg *targ = arg;
	unsigned long *pt = targ->pt;

	gettimeofday(&tv1, NULL);

	switch (targ->op) {
	case OP_RD:
		test_read(pt);
		break;
	case OP_WR:
		test_write(pt);
		break;
	default:
		abort();
		break;
	}

	gettimeofday(&tv2, NULL);
	show_diff_tv(targ->name, &tv2, &tv1);

	pthread_exit(NULL);
	return NULL;
}

void demo_good(void)
{
	int i;
	pthread_t t1, t2;
	struct good_struct good = {
		.t1 = 0,
		.t2 = 0,
	};
	struct thread_arg_pair {
		struct thread_arg arg[2];
	} pairs[] = {
		{
			(struct thread_arg){
				.name = "good1 thread1 (rd)",
				.op = OP_RD,
				.pt = &good.t1,
			},
			(struct thread_arg){
				.name = "good1 thread2 (rd)",
				.op = OP_RD,
				.pt = &good.t2,
			}
		},
		{
			(struct thread_arg){
				.name = "good2 thread1 (wr)",
				.op = OP_WR,
				.pt = &good.t1,
			},
			(struct thread_arg){
				.name = "good2 thread2 (wr)",
				.op = OP_WR,
				.pt = &good.t2,
			}
		},
		{
			(struct thread_arg){
				.name = "good3 thread1 (rd)",
				.op = OP_RD,
				.pt = &good.t1,
			},
			(struct thread_arg){
				.name = "good3 thread2 (wr)",
				.op = OP_WR,
				.pt = &good.t2,
			}
		},
	};

	for (i = 0; i < ARRAY_SIZE(pairs); i++) {
		pthread_create(&t1, NULL, thread_fn, &pairs[i].arg[0]);
		pthread_create(&t2, NULL, thread_fn, &pairs[i].arg[1]);

		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
	}
}

void demo_bad(void)
{
	int i;
	pthread_t t1, t2;
	struct bad_struct bad = {
		.t1 = 0,
		.t2 = 0,
	};

	struct thread_arg_pair {
		struct thread_arg arg[2];
	} pairs[] = {
		{
			(struct thread_arg){
				.name = "bad1 thread1 (rd)",
				.op = OP_RD,
				.pt = &bad.t1,
			},
			(struct thread_arg){
				.name = "bad1 thread2 (rd)",
				.op = OP_RD,
				.pt = &bad.t2,
			}
		},
		{
			(struct thread_arg){
				.name = "bad2 thread1 (wr)",
				.op = OP_WR,
				.pt = &bad.t1,
			},
			(struct thread_arg){
				.name = "bad2 thread2 (wr)",
				.op = OP_WR,
				.pt = &bad.t2,
			}
		},
		{
			(struct thread_arg){
				.name = "bad3 thread1 (rd)",
				.op = OP_RD,
				.pt = &bad.t1,
			},
			(struct thread_arg){
				.name = "bad3 thread2 (wr)",
				.op = OP_WR,
				.pt = &bad.t2,
			}
		},
	};

	for (i = 0; i < ARRAY_SIZE(pairs); i++) {
		pthread_create(&t1, NULL, thread_fn, &pairs[i].arg[0]);
		pthread_create(&t2, NULL, thread_fn, &pairs[i].arg[1]);

		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
	}
}

void usage(char *prog)
{
	fprintf(stderr, "Usage: %s [nloop=%ld] [good|bad]\n", prog, LOOP);
}

int main(int argc, char *argv[])
{
	int i;
	bool good, bad;

	if (argc < 2)
		usage(argv[0]);

	good = bad = true;

	for (i = 1; i < argc; i++) {
		if (!strncmp("nloop=", argv[i], 6)) {
			nloop = strtoul(argv[i] + 6, NULL, 10);
		} else if (!strcmp(argv[i], "good")) {
			good = true;
			bad = false;
		} else if (!strcmp(argv[i], "bad")) {
			good = false;
			bad = true;
		} else {
			fprintf(stderr, "Unknown arg %s\n", argv[i]);
			usage(argv[0]);
			exit(1);
		}
	}

	printf("nloop = %ld\n", nloop);

	if (good)
		demo_good();
	if (bad)
		demo_bad();

	printf("Done.\n");
}

