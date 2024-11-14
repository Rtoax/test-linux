// SPDX-License-Identifier: GPL-3.0
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

int x, y;

/* waw: Write After Write */
void *task1_waw(void *arg)
{
	y = 1;
	x = 2;
	return NULL;
}

void *task2_waw(void *arg)
{
	if (x == 2)
		assert(y == 1 && "Non-Sequentially Consistent");
	return NULL;
}

int main(void)
{
	size_t count = 0;
	pthread_t tasks[2];

	while (true) {
		x = y = 0;
		count++;

		pthread_create(&tasks[0], NULL, task1_waw, NULL);
		pthread_create(&tasks[1], NULL, task2_waw, NULL);

		pthread_join(tasks[0], NULL);
		pthread_join(tasks[1], NULL);

		if (count % 1000 == 0)
			fprintf(stderr, "Test count %ld\n", count);
	}

	fprintf(stderr, "Total test count %ld\n", count);

	return 0;
}
