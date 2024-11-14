// SPDX-License-Identifier: GPL-3.0
/**
 * Prove that the CPU executes out of order and use memory barriers to
 * eliminate the impact of out of order execution.
 */
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#include "barrier.h"

#if defined(HAVE_MRWBARRIER)
/* Could avoid out-of-order */
#define __test_barrier() smp_rwmb()
#elif defined(HAVE_MRBARRIER)
#define __test_barrier() smp_rmb()
#elif defined(HAVE_MWBARRIER)
#define __test_barrier() smp_wmb()
#elif defined(HAVE___sync_synchronize)
/* Could avoid out-of-order */
#define __test_barrier() __sync_synchronize()
#elif defined(HAVE___atomic_thread_fence__ATOMIC_RELAXED)
/* Could out-of-order */
#define __test_barrier() __atomic_thread_fence(__ATOMIC_RELAXED)
#elif defined(HAVE___atomic_thread_fence__ATOMIC_CONSUME)
/* Could out-of-order */
#define __test_barrier() __atomic_thread_fence(__ATOMIC_CONSUME)
#elif defined(HAVE___atomic_thread_fence__ATOMIC_ACQUIRE)
/* load barrier, could out-of-order */
#define __test_barrier() __atomic_thread_fence(__ATOMIC_ACQUIRE)
#elif defined(HAVE___atomic_thread_fence__ATOMIC_RELEASE)
/* store barrier, could out-of-order */
#define __test_barrier() __atomic_thread_fence(__ATOMIC_RELEASE)
#elif defined(HAVE___atomic_thread_fence__ATOMIC_ACQ_REL)
/**
 * store-load barrier, could out-of-order on x86_64, but aarch64 it's OK.
 */
#define __test_barrier() __atomic_thread_fence(__ATOMIC_ACQ_REL)
#elif defined(HAVE___atomic_thread_fence__ATOMIC_SEQ_CST)
/* Could avoid out-of-order */
#define __test_barrier() __atomic_thread_fence(__ATOMIC_SEQ_CST)
#elif defined(HAVE_NO_BARRIER)
/* Could out-of-order */
#define __test_barrier()
#else
#error "Nothing to do."
#endif

volatile int x, y, a, b;

void *task1(void *arg)
{
	a = 1;
	__test_barrier();
	x = b;
	pthread_exit(NULL);
}

void *task2(void *arg)
{
	b = 1;
	__test_barrier();
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
