#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>

#include "futex.h"

/* Test if FUTEX_WAIT thread are wake up in the order they wait. */

static int ft_wait;

void *wait(void *_tid)
{
	int ret;
	long tid = (long)_tid;
	printf(">>> T%ld FUTEX_WAIT\n", tid);
	ret = sys_futex(&ft_wait, FUTEX_WAIT, 0, NULL, NULL, 0);
	printf("<<< T%ld FUTEX_WAIT return %d\n", tid, ret);
	return NULL;
}

#define NTHR 10

int main(int argc, const char *argv[])
{
	long i = 0;
	pthread_t thr[NTHR];

	/* Test what happens if futex value does not equal to expected. */
	ft_wait = 1;
	pthread_t t1;
	pthread_create(&t1, NULL, wait, (void *)0);
	usleep(500);

	ft_wait = 0;
	for (i = 1; i <= NTHR; i++) {
		/* Ensure thread calling FUTEX_WAIT in order. */
		pthread_create(&thr[i], NULL, wait, (void *)i);
		usleep(500);
	}

	for (i = 1; i <= NTHR; i++) {
		printf("main wake up 1\n");
		sys_futex(&ft_wait, FUTEX_WAKE, 1, NULL, NULL, 0);
		usleep(500);
	}

	usleep(500);
	printf("all thread should have been waken now\n");

	return 0;
}
