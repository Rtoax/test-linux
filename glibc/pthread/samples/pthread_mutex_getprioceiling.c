#include <pthread.h>
#include <stdio.h>

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
	int prioceiling = 0;
	pthread_t thread_id;

	pthread_mutex_init(&mutex2, NULL);

	pthread_mutex_lock(&mutex2);
	pthread_mutex_getprioceiling(&mutex2, &prioceiling);
	pthread_mutex_unlock(&mutex2);

	printf("prioceiling = %d.\n", prioceiling);

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	pthread_join(thread_id, (void **)&pstatus);

	printf("pstatus = %d\n", *pstatus);

	pthread_mutex_destroy(&mutex2);

	return 0;
}
