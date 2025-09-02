// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2024-2025 Rong Tao */
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

int sys_affinity_bind(int cpu)
{
	cpu_set_t cpuset;
	int i, rc;

	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);

	rc = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
	if (rc) {
		perror("pthread_setaffinity_np failed");
		return rc;
	}

	/* check the actual affinity mask assigned to the thread */

	CPU_ZERO(&cpuset);

	rc = pthread_getaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
	if (rc) {
		perror("pthread_getaffinity_np failed");
		return rc;
	}

	fprintf(stderr, "set sys affinity: ");
	for (i = 0; i < CPU_SETSIZE; i++)
		if (CPU_ISSET(i, &cpuset))
			fprintf(stderr, "    CPU %d\n", i);

	if (!CPU_ISSET(cpu, &cpuset))
		fprintf(stderr, "affinity failed");

	return rc;
}
