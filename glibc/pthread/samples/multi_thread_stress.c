#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>


void* stress_fn(void* unused)
{
	pthread_exit(NULL);
	return NULL;
}

int main(int argc, char *argv[])
{
	int i;
	unsigned int nr_threads = 100;
	pthread_t *threads;

	if (argc < 2) {
		fprintf(stderr, "%s [nr-threads]\n", argv[0]);
		exit(1);
	}

	nr_threads = atoi(argv[1]);
	if (nr_threads < 1) {
		fprintf(stderr, "Wrong %s param\n", argv[1]);
		exit(1);
	}

	threads = (pthread_t *)malloc(nr_threads * sizeof(pthread_t));
	assert(threads && "malloc fatal");

	for (i = 0; i < nr_threads; i++)
		pthread_create(&threads[i], NULL, stress_fn, NULL);

	for (i = 0; i < nr_threads; i++)
		pthread_join(threads[i], NULL);

	free(threads);

	return 0;
}
