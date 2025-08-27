#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

#include "libs/log.h"


pthread_spinlock_t spinlock, spinlock2;

unsigned long pad0[7];
unsigned long latency = 0;
unsigned long pad1[7];
unsigned long total_latency = 0;
unsigned long pad2[7];
unsigned long total_num = 0;
unsigned long pad3[7];

unsigned long get_nsec(void)
{
	struct timespec t;

	clock_gettime(CLOCK_REALTIME, &t);

	return t.tv_sec * 1000000000UL + t.tv_nsec;
}

void *task_hold_spin(void *unused)
{
	log_child("task_hold_spin.\n");
	pthread_spin_lock(&spinlock2);

	while (1) {
		pthread_spin_lock(&spinlock);

		latency = get_nsec();

		pthread_spin_unlock(&spinlock2);

	}

	pthread_exit(NULL);

	return NULL;
}

void *task_get_spin(void *unused)
{
	log_child("task_get_spin.\n");

	while (1) {
		pthread_spin_lock(&spinlock2);

		total_latency += get_nsec() - latency;
		total_num++;

		if (total_num % 10000 == 0) {
			log_child
			    ("latency. per \033[1;31m%lf ns\033[m, msgs (total %ld).\n",
			     total_latency * 1.0 / total_num, total_num);
		}

		pthread_spin_unlock(&spinlock);

	}

	pthread_exit(NULL);

	return NULL;
}

int main(void)
{
	pthread_t t1, t2;

	pthread_spin_init(&spinlock, PTHREAD_PROCESS_SHARED);
	pthread_spin_init(&spinlock2, PTHREAD_PROCESS_SHARED);

	pthread_create(&t1, NULL, task_hold_spin, NULL);
	pthread_create(&t2, NULL, task_get_spin, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_spin_destroy(&spinlock);
	pthread_spin_destroy(&spinlock2);

	return 0;
}
