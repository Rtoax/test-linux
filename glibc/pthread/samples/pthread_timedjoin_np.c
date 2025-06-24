#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <pthread.h>
#include <stdio.h>
#include <time.h>

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
	struct timespec abstime = { 1, 1 };

	time_t abst = time(&abst);
	abstime.tv_sec = abst + 1;

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	pthread_timedjoin_np(thread_id, (void **)&pstatus, &abstime);

	printf("pstatus = %d\n", *pstatus);
	return 0;
}
