// SPDX-License-Identifier: GPL-3.0
/**
 * https://gcc.gnu.org/wiki/Atomic/GCCMM/AtomicSync
 */
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

/**
 * lock: Start two threads running at the same time
 */
int lock;
int x, y, z;

int should_end = false;

/**
 * war: Write After Read
 */

void *task1_war(void *arg)
{
	while (__atomic_load_n(&lock, __ATOMIC_RELAXED) != 1);

	x = 1;
	x = 2;
	return NULL;
}

void *task2_war(void *arg)
{
	while (__atomic_load_n(&lock, __ATOMIC_RELAXED) != 1);

	y = x;
	z = x;

	/* The assert cannot fail. */
	if (y > z) {
		/* end instead of assert() */
		should_end = true;
		fprintf(stderr, "ERROR: Nonsequentially Consistent happend!!\n");
	}
	return NULL;
}

int main(void)
{
	size_t count = 0;
	pthread_t tasks[2];

	while (!should_end) {
		__atomic_store_n(&lock, 0, __ATOMIC_RELAXED);

		x = y = z = 0;
		count++;

		pthread_create(&tasks[0], NULL, task1_war, NULL);
		pthread_create(&tasks[1], NULL, task2_war, NULL);

		/* Start test */
		__atomic_store_n(&lock, 1, __ATOMIC_RELAXED);

		pthread_join(tasks[0], NULL);
		pthread_join(tasks[1], NULL);

		if (count % 1000 == 0)
			fprintf(stderr, "Test count %ld\n", count);
	}

	fprintf(stderr, "Total test count %ld\n", count);

	return 0;
}
