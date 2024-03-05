/**
 * 2017-09-12	Rong Tao	Create this.
 * 2021-01-19	Rong Tao	Cal lantency
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>

sem_t sem_empty;
sem_t sem_empty1;

unsigned long latency = 0;
unsigned long total_latency = 0;
unsigned long total_num = 0;

static inline unsigned long nsecs(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000000000UL + ts.tv_nsec;
}

void *consums(void *arg)
{
	while (1) {
		sem_wait(&sem_empty1);

		total_latency += nsecs() - latency;
		total_num ++;

		if (total_num % 100000 == 0) {
			printf("latency. per msgs \033[1;31m%lf ns\033[m, msgs (total %ld).\n",
				total_latency * 1.0 / total_num, total_num);
		}
		sem_post(&sem_empty);
	}

	return NULL;
}

void *product(void *arg)
{
	sem_wait(&sem_empty1);

	sleep(1);

	while (1) {
		sem_wait(&sem_empty);
		latency = nsecs();
		sem_post(&sem_empty1);
	}
	return NULL;
}

int main(void)
{
	pthread_t ptid, ctid;

	sem_init(&sem_empty, 0, 1);
	sem_init(&sem_empty1, 0, 1);

	pthread_create(&ptid, NULL, product, NULL);

	pthread_create(&ctid, NULL, consums, NULL);

	pthread_join(ptid, NULL);
	pthread_join(ctid, NULL);

	sem_destroy(&sem_empty);
	sem_destroy(&sem_empty1);

	return 0;
}
