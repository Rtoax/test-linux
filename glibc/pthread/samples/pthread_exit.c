#include <pthread.h>
#include <stdio.h>

void *test_task_fn(void *unused)
{
	static int status = 12121;
	printf("test_task_fn.\n");
	pthread_exit(&status);
	return NULL;
}

int main(void)
{
	int *pstatus;
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, test_task_fn, NULL);
	pthread_join(thread_id, (void **)&pstatus);

	printf("pstatus = %d\n", *pstatus);
	return 0;
}
