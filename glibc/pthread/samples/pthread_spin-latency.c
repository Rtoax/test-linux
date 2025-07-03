#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "libs/log.h"

pthread_spinlock_t spinlock;
volatile unsigned long ticks_start = 0;
volatile unsigned long ticks_end = 0;

unsigned long get_nsec(void)
{
	struct timespec t;

	clock_gettime(CLOCK_REALTIME, &t);

	return t.tv_sec * 1000000000UL + t.tv_nsec;
}

void *task_hold_spin(void *unused)
{
	log_child("task_hold_spin.\n");

	pthread_spin_lock(&spinlock);

	sleep(1);

	ticks_start = get_nsec();

	pthread_spin_unlock(&spinlock);
	pthread_exit(NULL);
	return NULL;
}

void *task_get_spin(void *unused)
{
	log_child("task_get_spin.\n");

	sleep(1);
	pthread_spin_lock(&spinlock);

	ticks_end = get_nsec();

	pthread_spin_unlock(&spinlock);

	pthread_exit(NULL);
	return NULL;
}

int main(void)
{
	pthread_t t1, t2;

	pthread_spin_init(&spinlock, PTHREAD_PROCESS_SHARED);

	pthread_create(&t1, NULL, task_hold_spin, NULL);
	pthread_create(&t2, NULL, task_get_spin, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_spin_destroy(&spinlock);

	log_parent("Latency %ld ns\n", ticks_end - ticks_start);

	return 0;
}
