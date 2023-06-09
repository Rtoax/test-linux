#define _GNU_SOURCE
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

void* test_task_fn(void* unused)
{
	printf("child thread sleeping.\n");

	/* Disable cancel */
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

	/* Do some important job, that can't be cancelled */
	sleep(2);

	/* Enable cancel */
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

	/* Check cancel request queue, and try exit */
	pthread_testcancel();

	printf("Nobody give me a cancel.\n");

	/* Cancel immediate if cancel request received */
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

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

	printf("parent wait child thread to exit\n");
	pthread_timedjoin_np(thread_id, (void**)&pstatus, &abstime);
	printf("parent wait child thread to exit timeout\n");

	printf("parent cancel child thread\n");
	pthread_cancel(thread_id);

	printf("pstatus = %d\n", *pstatus);
	return 0;
}

