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
	int err, policy = SCHED_EXT;
	//struct sched_param param;

	// TODO: create EXT process.

	//param.sched_priority = 1;
	err = sched_setscheduler(0, policy, NULL);
	if (err < 0) {
		fprintf(stderr, "sched_setscheduler() failed, %m.\n");
		exit(1);
	}

	printf("Startup a %s task.\n", sched_policy_string(policy));

	while (1);

	return 0;
}
