/**
 * SCHED_EXT
 */
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/resource.h>
#include "sched_helpers.h"

int main(void)
{
	int err;
	unsigned long count = 0;
	struct sched_attr attr;

	attr.size = sizeof(attr);
	attr.sched_policy = SCHED_EXT;
	attr.sched_priority = 0;
	err = sys_sched_setattr(0, &attr, 0);
	if (err < 0) {
		fprintf(stderr, "sched_setattr() failed, %m.\n");
		exit(1);
	}

	printf("Startup a %s task.\n", sched_policy_string(attr.sched_policy));

	while (1) {
		sleep(1);
		printf("Count %ld\n", count++);
	}

	return 0;
}
