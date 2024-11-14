// SPDX-License-Identifier: GPL-3.0
/**
 * https://gcc.gnu.org/wiki/Atomic/GCCMM/AtomicSync
 */
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

/**
 * lock: Start two threads running at the same time
 */
int lock;
int x, y;

int should_end = false;

/**
 * Since threads don't need to be synchronized across the system, either
 * 'should_end = true' in this example can actually run.
 */

void *task1(void *arg)
{
	while (__atomic_load_n(&lock, __ATOMIC_RELAXED) != 1);

	__atomic_store_n(&y, 20, __ATOMIC_RELAXED);
	__atomic_store_n(&x, 10, __ATOMIC_RELAXED);

	return NULL;
}

void *task2(void *arg)
{
	while (__atomic_load_n(&lock, __ATOMIC_RELAXED) != 1);

	if (__atomic_load_n(&x, __ATOMIC_RELAXED) == 10) {
		if (__atomic_load_n(&y, __ATOMIC_RELAXED) != 20) {
			should_end = true;
			fprintf(stderr, "ERROR: Nonsequentially Consistent happend in task2!!\n");
			return NULL;
		}
		__atomic_store_n(&y, 10, __ATOMIC_RELAXED);
	}
	return NULL;
}

void *task3(void *arg)
{
	while (__atomic_load_n(&lock, __ATOMIC_RELAXED) != 1);

	if (__atomic_load_n(&y, __ATOMIC_RELAXED) == 10)
		if (__atomic_load_n(&x, __ATOMIC_RELAXED) != 10) {
			should_end = true;
			fprintf(stderr, "ERROR: Nonsequentially Consistent happend in task3!!\n");
			return NULL;
		}

	return NULL;
}

int main(void)
{
	size_t count = 0;
	pthread_t tasks[3];

	while (!should_end) {
		__atomic_store_n(&lock, 0, __ATOMIC_RELAXED);

		x = y = 0;
		count++;

		pthread_create(&tasks[0], NULL, task1, NULL);
		pthread_create(&tasks[1], NULL, task2, NULL);
		pthread_create(&tasks[2], NULL, task3, NULL);

		/* Start test */
		__atomic_store_n(&lock, 1, __ATOMIC_RELAXED);

		pthread_join(tasks[0], NULL);
		pthread_join(tasks[1], NULL);
		pthread_join(tasks[2], NULL);

		if (count % 1000 == 0)
			fprintf(stderr, "Test count %ld\n", count);
	}

	fprintf(stderr, "Total test count %ld\n", count);

	return 0;
}
