/**
 * Prove that the CPU executes out of order and use memory barriers to
 * eliminate the impact of out of order execution.
 *
 * 2021-05-26	Rong Tao	Create this.
 */
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#include "barrier.h"

#if defined(HAVE_MBARRIER)
/* Could avoid out-of-order */
#define mrwbarrier() smp_rwmb()
#define mrbarrier() smp_rmb()
#define mwbarrier() smp_wmb()
#elif defined(HAVE___sync_synchronize)
/* Could avoid out-of-order */
#define mrwbarrier() __sync_synchronize()
#define mrbarrier() __sync_synchronize()
#define mwbarrier() __sync_synchronize()
#elif defined(HAVE___atomic_thread_fence__ATOMIC_RELAXED)
/* Could out-of-order */
#define mrwbarrier() __atomic_thread_fence(__ATOMIC_RELAXED)
#define mrbarrier() __atomic_thread_fence(__ATOMIC_RELAXED)
#define mwbarrier() __atomic_thread_fence(__ATOMIC_RELAXED)
#elif defined(HAVE___atomic_thread_fence__ATOMIC_CONSUME)
/* Could out-of-order */
#define mrwbarrier() __atomic_thread_fence(__ATOMIC_CONSUME)
#define mrbarrier() __atomic_thread_fence(__ATOMIC_CONSUME)
#define mwbarrier() __atomic_thread_fence(__ATOMIC_CONSUME)
#elif defined(HAVE___atomic_thread_fence__ATOMIC_ACQUIRE)
/* Could out-of-order */
#define mrwbarrier() __atomic_thread_fence(__ATOMIC_ACQUIRE)
#define mrbarrier() __atomic_thread_fence(__ATOMIC_ACQUIRE)
#define mwbarrier() __atomic_thread_fence(__ATOMIC_ACQUIRE)
#elif defined(HAVE___atomic_thread_fence__ATOMIC_RELEASE)
/* Could out-of-order */
#define mrwbarrier() __atomic_thread_fence(__ATOMIC_RELEASE)
#define mrbarrier() __atomic_thread_fence(__ATOMIC_RELEASE)
#define mwbarrier() __atomic_thread_fence(__ATOMIC_RELEASE)
#elif defined(HAVE___atomic_thread_fence__ATOMIC_ACQ_REL)
/* Could out-of-order */
#define mrwbarrier() __atomic_thread_fence(__ATOMIC_ACQ_REL)
#define mrbarrier() __atomic_thread_fence(__ATOMIC_ACQ_REL)
#define mwbarrier() __atomic_thread_fence(__ATOMIC_ACQ_REL)
#elif defined(HAVE___atomic_thread_fence__ATOMIC_SEQ_CST)
/* Could avoid out-of-order */
#define mrwbarrier() __atomic_thread_fence(__ATOMIC_SEQ_CST)
#define mrbarrier() __atomic_thread_fence(__ATOMIC_SEQ_CST)
#define mwbarrier() __atomic_thread_fence(__ATOMIC_SEQ_CST)
#elif defined(HAVE_NO_BARRIER)
/* Could out-of-order */
#define mrwbarrier()
#define mrbarrier()
#define mwbarrier()
#else
#error "Nothing to do."
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
	size_t count = 0;
	pthread_t tasks[2];

	while (true) {
		x = y = a = b = 0;
		count++;

		pthread_create(&tasks[0], NULL, task1, NULL);
		pthread_create(&tasks[1], NULL, task2, NULL);

		pthread_join(tasks[0], NULL);
		pthread_join(tasks[1], NULL);

		if (x == 0 && y == 0) {
			fprintf(stderr, "WARNING: CPU Out of Order Exec.\n");
			break;
		}

		if (count % 1000 == 0)
			fprintf(stderr, "Test count %ld\n", count);
	}

	fprintf(stderr, "Total test count %ld\n", count);

	return 0;
}
