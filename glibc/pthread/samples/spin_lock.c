#include <pthread.h>
#include <stdio.h>
#include "libs/log.h"

pthread_spinlock_t spinlock;

#ifndef NR_THREADS
#define NR_THREADS	10
#endif

#define ADD_VAL	100000UL

static long int sum = 0;

void *test_task_fn(void *unused)
{
	int i;
	log_child("test_task_fn %ld.\n", pthread_self());
	for (i = 0; i < ADD_VAL; i++) {
		pthread_spin_lock(&spinlock);
		sum++;
		pthread_spin_unlock(&spinlock);
	}

	pthread_exit(NULL);
	return NULL;
}

int main(void)
{
	int i, ret = 0;
	pthread_t threads[NR_THREADS];

	pthread_spin_init(&spinlock, PTHREAD_PROCESS_SHARED);

	for (i = 0; i < NR_THREADS; i++)
		pthread_create(&threads[i], NULL, test_task_fn, NULL);

	for (i = 0; i < NR_THREADS; i++)
		pthread_join(threads[i], NULL);

	if (sum == NR_THREADS * ADD_VAL) {
		printf("Success call sum %ld\n", sum);
		ret = 0;
	} else {
		printf("Failed call sum %ld, expect %ld\n",
		       sum, NR_THREADS * ADD_VAL);
		ret = 1;
	}

	pthread_spin_destroy(&spinlock);
	return ret;
}
