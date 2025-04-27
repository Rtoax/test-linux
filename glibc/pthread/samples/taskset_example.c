#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>

#include <stdbool.h>
#include <err.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <syscall.h>

#include "pthread_helpers.h"

#define gettid() syscall(__NR_gettid)


struct task_arg {
	char cpu_list[128];
};

void *task_routine(void*arg)
{
	struct task_arg *Arg = ( struct task_arg *)arg;
	cpu_set_t cpu_set;
	int i;

	taskset(gettid(), Arg->cpu_list);

	while (1) {
		if (sched_getaffinity(gettid(), sizeof(cpu_set_t), &cpu_set)) {
			err(1, "sched_getaffinity");
		}
		printf("Process (%ld) bonds to CPU:", gettid());
		for (i = 0; i < CPU_SETSIZE; i++) {
			if (CPU_ISSET(i, &cpu_set)) {
				printf(" %d", i);
			}
		}
		printf("\n");
		sleep(3);
	}

	pthread_exit(NULL);
}

int main(int argc, char**argv)
{

	pthread_t task1, task2;

	struct task_arg task_args[] = {
		{"1,3"},
		{"2"},
	};

	pthread_create(&task1, NULL, task_routine, &task_args[0]);
	pthread_create(&task2, NULL, task_routine, &task_args[1]);

	pthread_setname_np(task1, "t1");
	pthread_setname_np(task2, "t2");

	pthread_join(task1, NULL);
	pthread_join(task2, NULL);

	return 0;
}

