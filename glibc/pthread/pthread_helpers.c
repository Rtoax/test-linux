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

void init_pi_mutex(pthread_mutex_t *m)
{
#define HAS_PRIORITY_INHERIT 1
#if HAS_PRIORITY_INHERIT
	pthread_mutexattr_t attr;
	int ret;
	int protocol;

	if ((ret = pthread_mutexattr_init(&attr)) != 0) {
		printf("Failed to init mutexattr: %d (%s)\n", ret,
		       strerror(ret));
	};
	if ((ret = pthread_mutexattr_setprotocol(&attr, PTHREAD_PRIO_INHERIT)) != 0) {
		printf("Can't set protocol prio inherit: %d (%s)\n", ret,
		       strerror(ret));
	}
	if ((ret = pthread_mutexattr_getprotocol(&attr, &protocol)) != 0) {
		printf("Can't get mutexattr protocol: %d (%s)\n", ret,
		       strerror(ret));
	}
	if ((ret = pthread_mutex_init(m, &attr)) != 0) {
		printf("Failed to init mutex: %d (%s)\n", ret, strerror(ret));
	}
#endif

	/* FIXME: does any of this need to be destroyed ? */
}

struct thread *thread_create(void *(*func)(void *), void *arg, int prio,
			     int policy)
{
	struct sched_param param;
	int ret;
	struct thread *thread;

	thread = malloc(sizeof(struct thread));
	if (!thread)
		return NULL;

	pthread_cond_init(&thread->cond, NULL);

	init_pi_mutex(&thread->mutex);
	thread->priority = prio;
	thread->policy = policy;
	thread->flags = 0;
	thread->arg = arg;
	thread->func = func;
	param.sched_priority = prio;

	pthread_attr_init(&thread->attr);
	pthread_attr_setinheritsched(&thread->attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&thread->attr, thread->policy);
	pthread_attr_setschedparam(&thread->attr, &param);

	if ((ret = pthread_create(&thread->pthread, &thread->attr, func,
				  (void *)thread))) {
		printf("pthread_create failed: %d (%s)\n", ret, strerror(ret));
		pthread_attr_destroy(&thread->attr);
		free(thread);
		return NULL;
	}

	return thread;
}

struct thread *thread_create_fifo(void *(*func)(void *), void *arg, int prio)
{
	return thread_create(func, arg, prio, SCHED_FIFO);
}

struct thread *thread_create_rr(void *(*func)(void *), void *arg, int prio)
{
	return thread_create(func, arg, prio, SCHED_RR);
}

struct thread *thread_create_other(void *(*func)(void *), void *arg)
{
	return thread_create(func, arg, 0, SCHED_OTHER);
}

int destroy_thread(struct thread *thread)
{
	if (!thread)
		return -EINVAL;
	pthread_attr_destroy(&thread->attr);
	free(thread);
	return 0;
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
