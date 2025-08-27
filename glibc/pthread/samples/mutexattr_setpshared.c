#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;
pthread_mutexattr_t mutexattr;

void *test_task1_fn(void *unused)
{
	printf("test_task1_fn.\n");

	pthread_mutex_lock(&mutex);

	printf("task1: .\n");

	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
	return NULL;
}

void *test_task2_fn(void *unused)
{
	printf("test_task2_fn.\n");

	pthread_mutex_lock(&mutex);

	printf("task2: .\n");

	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
	return NULL;
}

int main(void)
{
	int *pstatus;
	pthread_t thread_id1, thread_id2;

	pthread_mutexattr_init(&mutexattr);

	/**
	 * PTHREAD_PROCESS_SHARED	 用于同步该进程和其他进程中的线程
	 * PTHREAD_PROCESS_PRIVATE	 用于仅同步该进程中的线程
	 */
	pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_PRIVATE);

	pthread_mutex_init(&mutex, &mutexattr);

	pthread_create(&thread_id1, NULL, test_task1_fn, NULL);
	pthread_create(&thread_id2, NULL, test_task2_fn, NULL);

	pthread_join(thread_id1, (void **)&pstatus);
	pthread_join(thread_id1, (void **)&pstatus);

	pthread_mutex_destroy(&mutex);
	return 0;
}
