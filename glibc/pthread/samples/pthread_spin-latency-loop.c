#include <pthread.h>
#include <stdio.h>
#include <stdint.h>


pthread_spinlock_t spinlock, spinlock2;

unsigned long pad0[7];
unsigned long latency  = 0;
unsigned long pad1[7];
unsigned long total_latency = 0;
unsigned long pad2[7];
unsigned long total_num = 0;
unsigned long pad3[7];


#ifndef RDTSC
#define RDTSC() ({\
	register uint32_t a,d; \
	__asm__ __volatile__( "rdtsc" : "=a"(a), "=d"(d)); \
	(((uint64_t)a)+(((uint64_t)d)<<32)); \
	})
#endif

void* task_hold_spin(void* unused)
{
	printf("task_hold_spin.\n");
	pthread_spin_lock(&spinlock2);

	while (1) {
		pthread_spin_lock(&spinlock);

		latency = RDTSC();

		pthread_spin_unlock(&spinlock2);

	}
	pthread_exit(NULL);
	return NULL;
}

void* task_get_spin(void* unused)
{
	printf("task_get_spin.\n");

	while (1) {
		pthread_spin_lock(&spinlock2);

		total_latency += RDTSC() - latency;
		total_num ++;

		if (total_num % 10000 == 0) {

			printf("latency. ticks %lf, per msgs \033[1;31m%lf ns\033[m, msgs (total %ld).\n",
				total_latency*1.0/total_num,
				total_latency*1.0/total_num/2700000000*1000000000, total_num);

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
