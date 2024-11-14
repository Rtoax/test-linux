// SPDX-License-Identifier: GPL-3.0
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

/**
 * lock: Start two threads running at the same time
 */
int lock;
int x, y;

/* waw: Write After Write */
void *task1_waw(void *arg)
{
	while (__atomic_load_n(&lock, __ATOMIC_RELAXED) != 1);

	y = 1;
	x = 2;
	return NULL;
}

void *task2_waw(void *arg)
{
	while (__atomic_load_n(&lock, __ATOMIC_RELAXED) != 1);

	if (x == 2)
		assert(y == 1 && "Nonsequentially Consistent happend!!");
	return NULL;
}

int main(void)
{
	size_t count = 0;
	pthread_t tasks[2];

	while (true) {
		__atomic_store_n(&lock, 0, __ATOMIC_RELAXED);

		x = y = 0;
		count++;

		pthread_create(&tasks[0], NULL, task1_waw, NULL);
		pthread_create(&tasks[1], NULL, task2_waw, NULL);

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
