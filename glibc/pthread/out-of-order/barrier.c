/**
 * 证明CPU乱序执行，并使用内存屏障消除乱序执行的影响
 *
 * 2021-05-26	Rong Tao	Create this.
 */
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#include "barrier.h"

#define __unused __attribute__((unused))

#if defined(HAVE_MBARRIER)
static void __unused inline mrwbarrier() { smp_rwmb(); }
static void __unused inline mrbarrier()  { smp_rmb(); }
static void __unused inline mwbarrier()  { smp_wmb(); }
#else
#define mrwbarrier()
#define mrbarrier()
#define mwbarrier()
#endif

volatile int x, y, a, b;

void *task1(void *arg)
{
	a = 1;
	mrwbarrier();
	x = b;
	pthread_exit(NULL);
}

void *task2(void *arg)
{
	b = 1;
	mrwbarrier();
	y = a;
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t tasks[2];

	while (true) {
		x = y = a = b = 0;

		pthread_create(&tasks[0], NULL, task1, NULL);
		pthread_create(&tasks[1], NULL, task2, NULL);

		pthread_join(tasks[0], NULL);
		pthread_join(tasks[1], NULL);

		if (x == 0 && y == 0) {
			fprintf(stderr, "WARNING: CPU Out of Order Exec.\n");
			break;
		}
	}

	return 0;
}
