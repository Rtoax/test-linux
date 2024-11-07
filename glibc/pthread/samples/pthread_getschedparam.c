#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

const char *strschedpolicy(int policy)
{
	switch (policy) {
	case SCHED_FIFO: return "SCHED_FIFO";
	case SCHED_RR: return "SCHED_RR";
	case SCHED_OTHER: return "SCHED_OTHER";
	}
	return "???";
}

void getschedparam(void)
{
	struct sched_param sched_param;
	int policy;

	pthread_getschedparam(pthread_self(), &policy, &sched_param);

	printf("Policy %s, prio %d\n", strschedpolicy(policy),
		sched_param.sched_priority);
}

void *routinue(void *unused)
{
	pthread_setname_np(pthread_self(), "pthread-child");

	getschedparam();

	return NULL;
}

int main(void)
{
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, &routinue, NULL);

	pthread_setname_np(pthread_self(), "pthread-parent");

	getschedparam();

	pthread_join(thread_id, NULL);

	return 0;
}
