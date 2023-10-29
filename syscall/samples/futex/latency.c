#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <linux/futex.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "futex.h"


#ifndef RDTSC
#define RDTSC() ({ \
		register uint32_t a, d; \
		__asm__ __volatile__("rdtsc" : "=a"(a), "=d"(d)); \
		(((uint64_t)a) + (((uint64_t)d) << 32)); \
	})
#endif

int futex_1 = 1;
int futex_2 = 1;

unsigned long latency = 0;
unsigned long total_latency = 0;
unsigned long total_num = 0;

static void fwait(int *futexp, int val)
{
	int s;
	while (1) {
		s = futex(futexp, FUTEX_WAIT, val, NULL, NULL, 0);
		if (s == -1 && errno != EAGAIN){
			exit(0);
		}

		if (s == 0){
			return;
		}
	}
}

static int fwake(int *futexp)
{
	int s = 0;
	s = futex(futexp, FUTEX_WAKE, 1, NULL, NULL, 0);
	if (s  == -1)
		exit(0);
	return s;
}

void* worker1(void* param)
{
	while (1) {
		fwait(&futex_1, 1);
		total_latency += RDTSC() - latency;
		total_num++;

		if (total_num % 10000 == 0) {
			/* TODO: calculate accurate latency */
			printf("latency. ticks %lf, per msgs \033[1;31m%lf ns\033[m, msgs (total %ld).\n",
				total_latency * 1.0 / total_num,
				total_latency * 1.0 / total_num / 3000000000 * 1000000000, total_num);
		}
		fwait(&futex_2, 1);
	}
	return NULL;
}

void* worker2(void* param)
{
	while (1) {
		fwake(&futex_2);
		latency = RDTSC();
		fwake(&futex_1);
	}
	return NULL;
}

int main(void)
{
	pthread_t write_taskid, read_taskid;

	pthread_create(&write_taskid, NULL, worker1, NULL);
	pthread_create(&read_taskid, NULL, worker2, NULL);

	pthread_join(write_taskid, NULL);
	pthread_join(read_taskid, NULL);

	printf("Exit.\n");
	return 0;
}