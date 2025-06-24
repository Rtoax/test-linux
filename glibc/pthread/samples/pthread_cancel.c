/**
 * Pthread cancel.
 *
 * PTHREAD_CANCEL_ENABLE: default
 * PTHREAD_CANCEL_DISABLE
 * PTHREAD_CANCEL_DEFFERED: Valid when the Cancel status is Enable, After
 *                          receiving the signal, continue to run until the next
 *                          cancellation point and then exit
 * PTHREAD_CANCEL_ASYNCHRONOUS: Valid when the Cancel status is Enable,
 *                              Cancel execution as soon as the signal is received
 *
 * Cancel Point:
 * 1. pthread_testcancel()
 * 2. pthread_cond_wait, pthread_cond_timewait
 * 3. sigwait
 * 4. standerd lib function
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

void cleanup_handler(void *arg)
{
	printf("cleanup_handler.\n");
}

void *test_task_fn(void *unused)
{
	printf("child thread sleeping.\n");

	pthread_cleanup_push(cleanup_handler, NULL);

	/**
	 * Disable cancel
	 * 线程准备执行一些关键工作，在这个过程中不希望被取消
	 * 所以先通过pthread_setcancelstate()将本线程的cancel state 设为disabled
	 */
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

	/* Do some important job, that can't be cancelled */
	printf("do something.\n");
	sleep(2);

	/**
	 * Enable cancel
	 * 键工作执行完成，可以被取消
	 * 通过pthread_setcancelstate()将本线程的cancel state 设为enabled
	 */
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

	/**
	 * Check cancel request queue, and try exit
	 * 调用pthread_testcancel()函数，检查一下在cancel state 为disabled状态的
	 * 时候，是否有取消请求发送给本线程。如果有的话就取消（退出）.
	 */
	printf("test cancel start...\n");
	pthread_testcancel();
	printf("test cancel done.\n");

	/**
	 * pthread_testcancel()返回了，表明之前没有取消请求发送给本线程
	 * 继续其余的工作.
	 * 这时候如果有取消请求发送给本线程，会在下一次执行到cancellation point
	 * 的时候(例如sleep(), read(), write(), ...)时取消。
	 */
	printf("Nobody give me a cancel.\n");

	/**
	 * Cancel immediate if cancel request received
	 * 从这里开始，函数里不再包含cancellation point了
	 * 如果收到取消请求，将无法取消。所以先把本线程的cancel type
	 * 设为asynchronous异步，收到取消请求将立即取消。
	 */
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	pthread_cleanup_pop(1);

	static int status = 12121;

	printf("thread normal exit\n");
	pthread_exit(&status);
	return NULL;
}

int main(void)
{
	int *pstatus;
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	struct timespec abstime = { 1, 1 };
	time_t abst = time(&abst);
	abstime.tv_sec = abst + 3;

	printf("parent wait child thread to exit\n");
	pthread_timedjoin_np(thread_id, (void **)&pstatus, &abstime);
	printf("parent wait child thread to exit timeout\n");

	printf("parent cancel child thread\n");
	pthread_cancel(thread_id);

	printf("pstatus = %d\n", *pstatus);
	return 0;
}
