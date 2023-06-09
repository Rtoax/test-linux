#define _GNU_SOURCE
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

void* test_task_fn(void* unused)
{
	printf("child thread sleeping.\n");

	sleep(2);

	static int status = 12121;

	printf("thread normal exit\n");
	pthread_exit(&status);
	return NULL;
}

int main (void)
{
	int *pstatus;
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	struct timespec abstime = {1, 1};
	time_t abst = time(&abst);
	abstime.tv_sec = abst + 1;

	printf("parent wait child thread exit\n");
	pthread_timedjoin_np(thread_id, (void**)&pstatus, &abstime);

	printf("parent cancel child thread\n");
	pthread_cancel(thread_id);

	printf("pstatus = %d\n", *pstatus);
	return 0;
}

