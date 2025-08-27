#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <pthread.h>
#include <stdio.h>

void *test_task_fn(void *unused)
{
	printf("test_task_fn.\n");

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
	/* pthread_yield is deprecated, use sched_yield instead */
	pthread_yield();
#pragma GCC diagnostic pop

	static int status = 12121;
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
