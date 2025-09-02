#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>

#include "pthread_helpers.h"
#include "create_thread.h"

#define HAS_PRIORITY_INHERIT 1

void init_pi_mutex(pthread_mutex_t *m)
{
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

struct thread *create_thread(void *(*func)(void *), void *arg, int prio,
			     int policy)
{
	struct sched_param param;
	int ret;
	struct thread *thread;

	thread = malloc(sizeof(struct thread));
	if (!thread)
		return NULL;

	pthread_cond_init(&thread->cond, NULL);	// Accept the defaults
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
	pthread_attr_destroy(&thread->attr);

	return thread;
}

struct thread *create_fifo_thread(void *(*func)(void *), void *arg, int prio)
{
	return create_thread(func, arg, prio, SCHED_FIFO);
}

struct thread *create_rr_thread(void *(*func)(void *), void *arg, int prio)
{
	return create_thread(func, arg, prio, SCHED_RR);
}

struct thread *create_other_thread(void *(*func)(void *), void *arg)
{
	return create_thread(func, arg, 0, SCHED_OTHER);
}

#ifdef MAIN_TEST
struct args {
	int cpu;
};

void *loop(void *arg)
{
	struct thread *t = arg;
	struct args *a = (struct args *)t->arg;

	fprintf(stderr, "Try set cpu affinity %d\n", a->cpu);
	sys_affinity_bind(a->cpu);
	while (true) ;
	return NULL;
}

int main(void)
{
	struct thread *threads[3];

	struct args args[3] = {
		{
		 .cpu = 1,
		 },
		{
		 .cpu = 2,
		 },
		{
		 .cpu = 3,
		 },
	};

	threads[0] = create_fifo_thread(loop, &args[0], 99);
	threads[1] = create_rr_thread(loop, &args[1], 99);
	threads[2] = create_other_thread(loop, &args[2]);
	if (!threads[0] || !threads[1] || !threads[2])
		goto failed;

	pthread_join(threads[0]->pthread, NULL);
	pthread_join(threads[1]->pthread, NULL);
	pthread_join(threads[2]->pthread, NULL);

	return 0;
 failed:
	return -1;
}
#endif
