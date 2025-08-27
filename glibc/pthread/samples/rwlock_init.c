
#include <pthread.h>
#include <stdio.h>

pthread_rwlock_t rwlock1 = PTHREAD_RWLOCK_INITIALIZER;
pthread_rwlock_t rwlock2;

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

	pthread_rwlock_init(&rwlock2, NULL);

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	pthread_join(thread_id, (void **)&pstatus);

	printf("pstatus = %d\n", *pstatus);

	pthread_rwlock_destroy(&rwlock2);

	return 0;
}
