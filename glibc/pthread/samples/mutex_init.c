#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2;

void *test_task_fn(void *unused)
{
	printf("test_task_fn.\n");

	static int status = 12121;

	pthread_exit(&status);
	return NULL;
}

int main(void)
{
	int *pstatus;
	pthread_t thread_id;

	pthread_mutex_init(&mutex2, NULL);

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	pthread_join(thread_id, (void **)&pstatus);

	printf("pstatus = %d\n", *pstatus);

	pthread_mutex_destroy(&mutex2);

	return 0;
}
