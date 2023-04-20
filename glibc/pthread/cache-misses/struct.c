/**
 * cache-misses.c - Test the program efficiency problems caused by the
 * influence of data structures on cache misses.
 *
 * Copyright (C) CESTC, CO.
 *
 * 2023-04-15	Rong Tao	Create this.
 */
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

#define LOOP	100000000L

/**
 * Two threads accessing t1 and t2 at the same time (usually writes), this
 * access should be avoided, if it cannot be avoided, it should be ensured
 * that t1 and t2 are not in the same cache line, otherwise, when writing t1,
 * t2 and t1 are in a cache line, causing t2 to invalidate in the cache.
 */
struct good_struct {
	unsigned long t1;
#if defined(L3_CACHELINE_SIZE)
	char pad[L3_CACHELINE_SIZE];
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

void show_diff_tv(const char *name, struct timeval *end, struct timeval *start)
{
	printf("%16s: %ld us\n",
		name,
		(end->tv_sec - start->tv_sec) * 1000000
		+ (end->tv_usec - start->tv_usec));
}

struct thread_arg {
	char *name;
	unsigned long *pt;
};
void* thread_fn(void *arg)
{

	struct timeval tv1, tv2;
	struct thread_arg *targ = arg;
	unsigned long int i;
	unsigned long *pt = targ->pt;

	gettimeofday(&tv1, NULL);

	for(i = 0; i < LOOP; i++)
		*pt += 1;

	gettimeofday(&tv2, NULL);
	show_diff_tv(targ->name, &tv2, &tv1);

	pthread_exit(NULL);
	return NULL;
}

void demo_good(void)
{
	pthread_t t1, t2;
	struct good_struct good = {
		.t1 = 0,
		.t2 = 0,
	};
	struct thread_arg targ1 = {
		.name = "good thread1",
		.pt = &good.t1,
	};
	struct thread_arg targ2 = {
		.name = "good thread2",
		.pt = &good.t2,
	};
	pthread_create(&t1, NULL, thread_fn, &targ1);
	pthread_create(&t2, NULL, thread_fn, &targ2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}

void demo_bad(void)
{
	pthread_t t1, t2;
	struct bad_struct bad = {
		.t1 = 0,
		.t2 = 0,
	};
	struct thread_arg targ1 = {
		.name = "bad thread1",
		.pt = &bad.t1,
	};
	struct thread_arg targ2 = {
		.name = "bad thread2",
		.pt = &bad.t2,
	};
	pthread_create(&t1, NULL, thread_fn, &targ1);
	pthread_create(&t2, NULL, thread_fn, &targ2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}

int main(int argc, char *argv[])
{
	demo_good();
	demo_bad();

	printf("Done.\n");
}

