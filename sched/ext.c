/**
 * SCHED_EXT
 */
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/resource.h>
#include "sched_helpers.h"

int main(int argc, char *argv[])
{
	int err, policy;
	unsigned long count = 0;

	policy = SCHED_EXT;
#if 0
	struct sched_attr attr;

	attr.size = sizeof(attr);
	attr.sched_policy = policy;
	attr.sched_priority = 0;
	err = sys_sched_setattr(0, &attr, 0);
#else
	struct sched_param param;
	param.sched_priority = 0;
	err = sched_setscheduler(0, policy, &param);
#endif
	if (err < 0) {
		fprintf(stderr, "set sched ext failed, %m.\n");
		exit(1);
	}

	printf("Startup a %s task.\n",
		sched_policy_string(sched_getscheduler(getpid())));

	while (1) {
		sleep(1);
		printf("Count %ld\n", count++);
	}

	return 0;
}
