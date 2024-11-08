/**
 * See $ top -Hp $(pidof nice-latency)
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>


struct thread_arg {
	int id;
	int prio; /* nice value, set by setpriority(PRIO_PROCESS, 0, prio); */
	unsigned long spent;
};


static inline unsigned long usecs(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000UL + tv.tv_usec;
}

static inline __attribute__((optimize("-O0")))
unsigned long do_something(void)
{
#define NLOOP	2000000000UL
	unsigned long i, sum = 0;
	for (i = 0; i < NLOOP; i++)
		sum += i;
	return sum;
}

void *routinue(void *arg)
{
	int err;
	struct thread_arg *targ = arg;
	char name[64];
	unsigned long start, end;

	sprintf(name, "T%02d:prio(%d)", targ->id, targ->prio);

	pthread_setname_np(pthread_self(), name);

	err = setpriority(PRIO_PROCESS, 0, targ->prio);
	if (err == -1) {
		fprintf(stderr, "setpriority %m\n");
		abort();
	}

	start = usecs();
	do_something();
	end = usecs();

	targ->spent = end - start;

	return NULL;
}

/* nice value: +19 (low priority) to -20 (high priority) */
#define NR_THREAD	(19 - (-20) + 1)

int main(void)
{
	int i;
	pthread_t threads[NR_THREAD];
	struct thread_arg targs[NR_THREAD];


	pthread_setname_np(pthread_self(), "MAIN");

	for (i = 0; i < NR_THREAD; i++) {
		targs[i].id = i;
		targs[i].prio = i - 20;
		pthread_create(&threads[i], NULL, &routinue, &targs[i]);
	}

	for (i = 0; i < NR_THREAD; i++)
		pthread_join(threads[i], NULL);

	printf("%-8s %-8s %-8s\n", "ID", "NICE", "SPENT(us)");
	for (i = 0; i < NR_THREAD; i++)
		printf("%-8d %-8d %-8ld\n", targs[i].id, targs[i].prio,
			targs[i].spent);

	return 0;
}
