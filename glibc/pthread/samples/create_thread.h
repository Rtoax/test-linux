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

void init_pi_mutex(pthread_mutex_t *m);

struct thread *create_thread(void *(*func)(void *), void *arg, int prio,
			     int policy);

struct thread *create_fifo_thread(void *(*func)(void *), void *arg, int prio);

struct thread *create_rr_thread(void *(*func)(void *), void *arg, int prio);
struct thread *create_other_thread(void *(*func)(void *), void *arg);

