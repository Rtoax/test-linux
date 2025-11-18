/**
 * round-robin
 */
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

int main(void)
{
	int err;
	struct sched_param param;

	param.sched_priority = 99;
	err = sched_setscheduler(0, SCHED_RR, &param);
	if (err < 0) {
		fprintf(stderr, "sched_setscheduler() failed, %m.\n");
		exit(1);
	}

	printf("Startup a RR task.\n");

	while (1);

	return 0;
}
