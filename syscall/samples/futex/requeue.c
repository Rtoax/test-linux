#include "futex.h"
#include <linux/futex.h>
#include <pthread.h>
#include <stdio.h>

/**
 * After FUTEX_REQUEUE, the waiting thread is waken up by FUTEX_WAKE on the new
 * futex instead of the original one specified when calling FUTEX_WAIT.
 */

static int ft_wait;
static int ft_requ;

void *wait(void *dummy)
{
	printf("\033[31mfutex_wait on ft_wait\033[m\n");
	sys_futex(&ft_wait, FUTEX_WAIT, ft_wait, NULL, NULL, 0);
	printf("\033[31mfutex_wait on ft_wait returned\033[m\n");
	return NULL;
}

void *wake(void *dummy)
{
	sleep(1);
	printf("requeue from ft_wait to ft_requ\n");
	sys_futex(&ft_wait, FUTEX_REQUEUE, 0, (void *)1, &ft_requ, 0);

	sleep(1);
	printf("futex_wake on ft_wait\n");
	/**
	 * This will not wake up the wait thread, as it has been moved from ft_wait
	 * futex.
	 */
	sys_futex(&ft_wait, FUTEX_WAKE, 1, NULL, NULL, 0);

	sleep(1);
	printf("futex_wake on ft_requ\n");
	/* This will wake up the wait thread. */
	sys_futex(&ft_requ, FUTEX_WAKE, 1, NULL, NULL, 0);

	return NULL;
}

int main(int argc, const char *argv[])
{
	pthread_t thr_wait, thr_wake;

	pthread_create(&thr_wait, NULL, wait, NULL);
	pthread_create(&thr_wake, NULL, wake, NULL);

	pthread_join(thr_wait, NULL);
	pthread_join(thr_wake, NULL);

	return 0;
}

