// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2024-2025 Rong Tao */
#pragma once
#include <pthread.h>

struct thread {
	pthread_t pthread;
	pthread_attr_t attr;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	void *arg;
	void *(*func)(void *);
	int priority;
	int policy;
	int flags;
};


pthread_t start_thread(void *(*routine)(void *), int cpu, void *arg);

void init_pi_mutex(pthread_mutex_t *m);

struct thread *thread_create(void *(*func)(void *), void *arg, int prio,
			     int policy);

struct thread *thread_create_fifo(void *(*func)(void *), void *arg, int prio);

struct thread *thread_create_rr(void *(*func)(void *), void *arg, int prio);
struct thread *thread_create_other(void *(*func)(void *), void *arg);

int destroy_thread(struct thread *thread);

int sys_affinity_bind(int cpu);
