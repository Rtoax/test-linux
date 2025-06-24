#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sched.h>
#include <pthread.h>
#include <stdio.h>

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
