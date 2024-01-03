#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NR_THREAD   10

pthread_barrier_t barrier;
pthread_barrierattr_t barrierattr;

void *test_task_fn(void *unused)
{
	printf("test_task_fn %ld.\n", (unsigned long)pthread_self());

	sleep((unsigned long)pthread_self() % NR_THREAD);

	pthread_barrier_wait(&barrier);

	printf("thread %ld done.\n", (unsigned long)pthread_self());

	pthread_exit(NULL);
	return NULL;
}

/* The main program. */
int main(void)
{
	int i;
	pthread_t threadids[NR_THREAD];

	pthread_barrierattr_init(&barrierattr);
	pthread_barrierattr_setpshared(&barrierattr, PTHREAD_PROCESS_SHARED);

	pthread_barrier_init(&barrier, &barrierattr, NR_THREAD);

	for (i = 0; i < NR_THREAD; i++)
		pthread_create(&threadids[i], NULL, test_task_fn, NULL);

	for (i = 0; i < NR_THREAD; i++)
		pthread_join(threadids[i], NULL);

	pthread_barrier_destroy(&barrier);
	pthread_barrierattr_destroy(&barrierattr);

	return 0;
}
