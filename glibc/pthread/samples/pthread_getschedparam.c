#define _GNU_SOURCE
#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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
	int err;
	pthread_t child;
	struct sched_param sched_param;
	int policy;

	pthread_create(&child, NULL, &routinue, NULL);

	pthread_setname_np(pthread_self(), "pthread-parent");

	policy = SCHED_RR;
	sched_param.sched_priority = 99;

	err = pthread_setschedparam(pthread_self(), policy, &sched_param);
	if (err) {
		switch (err) {
		case EPERM:
			fprintf(stderr, "No permission.\n");
			break;
		default:
			fprintf(stderr, "ERROR: %s.\n", strerror(err));
			break;
		}
	}

	getschedparam();

	pthread_join(child, NULL);

	return 0;
}
