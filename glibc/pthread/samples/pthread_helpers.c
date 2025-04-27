#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
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


pthread_t start_thread(void *(*routine)(void *), int cpu, void *arg)
{
	pthread_t thread;
	pthread_attr_t attr, *pattr = NULL;
	cpu_set_t cpuset;

	pthread_attr_init(&attr);

	if (cpu >= 0) {
		CPU_ZERO(&cpuset);
		CPU_SET(cpu, &cpuset);
		pthread_attr_setaffinity_np(&attr, sizeof(cpuset), &cpuset);
		pattr = &attr;
	}

	if (pthread_create(&thread, pattr, routine, arg) != 0) {
		printf("Failed to start thread\n");
		exit(1);
	}

	pthread_attr_destroy(&attr);

	return thread;
}

