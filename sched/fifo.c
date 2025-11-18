/**
 * first-in, first-out
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
	err = sched_setscheduler(0, SCHED_FIFO, &param);
	if (err < 0) {
		fprintf(stderr, "sched_setscheduler() failed, %m.\n");
		exit(1);
	}

	printf("Startup a FIFO task.\n");

	while (1);

	return 0;
}
