#include <pthread.h>
#include <stdio.h>

void* test_task_fn(void* unused)
{
	printf(">>pthread_self() = %ld\n", pthread_self());

	static int status = 12121;

	printf(">>pthread_self() = %ld\n", pthread_self());

	pthread_exit(&status);
	return NULL;
}

int main ()
{
	int *pstatus;
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	pthread_join(thread_id, (void**)&pstatus);

	printf("pthread_self() = %ld\n", pthread_self());
	return 0;
}

