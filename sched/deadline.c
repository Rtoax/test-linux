#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sched_helpers.h"

int main(void)
{
	int err;
	struct sched_attr attr;

	attr.size = sizeof(attr);
	attr.sched_flags = 0;
	attr.sched_nice = 0;
	attr.sched_priority = 0;

	/* This creates a 10ms/30ms reservation */
	attr.sched_policy = SCHED_DEADLINE;
	attr.sched_runtime = 10 * 1000 * 1000;
	attr.sched_period = attr.sched_deadline = 30 * 1000 * 1000;

	err = sys_sched_setattr(0, &attr, 0);
	if (err < 0) {
		fprintf(stderr, "sched_setattr() failed, %m.\n");
		exit(1);
	}

	printf("Startup a deadline task.\n");

	while (1);

	return 0;
}
