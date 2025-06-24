#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <pthread.h>
#include <stdio.h>

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

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	pthread_tryjoin_np(thread_id, (void **)&pstatus);

	printf("pstatus = %d\n", *pstatus);

	return 0;
}
