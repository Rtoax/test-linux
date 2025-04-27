/**
 * https://www.kernel.org/doc/Documentation/scheduler/sched-deadline.txt
 */
#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <sys/syscall.h>
#include <pthread.h>

#include "pthread_helpers.h"

#define gettid() syscall(__NR_gettid)

#define SCHED_DEADLINE 6

static volatile int done;

void *run_deadline(void *data)
{
	struct __sched_attr attr;
	int x = 0;
	int ret;
	unsigned int flags = 0;

	printf("deadline thread started [%ld]\n", gettid());

	attr.size = sizeof(attr);
	attr.sched_flags = 0;
	attr.sched_nice = 0;
	attr.sched_priority = 0;

	/* This creates a 10ms/30ms reservation */
	attr.sched_policy = SCHED_DEADLINE;
	attr.sched_runtime = 10 * 1000 * 1000;
	attr.sched_period = attr.sched_deadline = 30 * 1000 * 1000;

	ret = sys_sched_setattr(0, &attr, flags);
	if (ret < 0) {
		done = 0;
		perror("sys_sched_setattr");
		exit(-1);
	}

	while (!done) {
		x++;
	}

	printf("deadline thread dies [%ld]\n", gettid());
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t thread;

	printf("main thread [%ld]\n", gettid());

	pthread_create(&thread, NULL, run_deadline, NULL);

	sleep(2);

	done = 1;
	pthread_join(thread, NULL);

	printf("main dies [%ld]\n", gettid());
	return 0;
}
