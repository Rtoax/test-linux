#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <linux/futex.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "futex.h"

struct worker_args {
	int *futex_1;
	int *futex_2;
};

#define NUM_OF_THREADS 2

static void fwait(int *futexp, int val)
{
	int s;
	while (1) {
		s = futex(futexp, FUTEX_WAIT, val, NULL, NULL, 0);
		if (s == -1 && errno != EAGAIN)
			exit(0);
		if (s == 0)
			return;
	}
}

static int fwake(int *futexp)
{
	int s = 0;
	s = futex(futexp, FUTEX_WAKE, 1, NULL, NULL, 0);
	if (s == -1)
		exit(0);
	return s;
}

void *worker(void *param)
{
	int i;

	for (i = 0; i < 10; i++) {
		fwait(((struct worker_args *)param)->futex_1, 1);
		printf("[Thread]\n");
		fwait(((struct worker_args *)param)->futex_2, 1);
	}
	return NULL;
}

int main(void)
{
	int i;
	int futex_1 = 1;
	int futex_2 = 1;
	int num_of_awakes;
	struct worker_args args;

	pthread_t threads[NUM_OF_THREADS];

	memset(threads, 0, sizeof(threads));

	args.futex_1 = &futex_1;
	args.futex_2 = &futex_2;

	for (i = 0; i < NUM_OF_THREADS; i++)
		pthread_create(&threads[i], NULL, worker, (void *)&args);

	for (i = 0; i < 10; i++) {
		num_of_awakes = 0;
		while (num_of_awakes < NUM_OF_THREADS)
			num_of_awakes += fwake(&futex_1);

		sleep(1);
		printf("[Main]\n");

		num_of_awakes = 0;
		while (num_of_awakes < NUM_OF_THREADS)
			num_of_awakes += fwake(&futex_2);
	}

	for (i = 0; i < NUM_OF_THREADS; i++)
		pthread_join(threads[i], NULL);

	return 0;
}
