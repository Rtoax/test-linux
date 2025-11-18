/**
 * round-robin
 */
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/resource.h>

int main(void)
{
	int err;
	struct sched_param param;
	struct rlimit rlimit;

	param.sched_priority = 1;
	err = sched_setscheduler(0, SCHED_RR, &param);
	if (err < 0) {
		fprintf(stderr, "sched_setscheduler() failed, %m.\n");
		exit(1);
	}

	err = getrlimit(RLIMIT_RTTIME, &rlimit);
	if (err < 0) {
		fprintf(stderr, "getrlimit() failed, %m.\n");
		exit(1);
	}

	/* see /proc/sys/kernel/sched_rt_period_us */
	rlimit.rlim_cur *= 1000000;
	rlimit.rlim_max *= 1000000;
	err = setrlimit(RLIMIT_RTTIME, &rlimit);
	if (err < 0) {
		fprintf(stderr, "setrlimit() failed, %m.\n");
		exit(1);
	}

	printf("Startup a RR task.\n");

	/**
	 * infinite loop will be killed if not setrlimit, see sched(7).
	 */
	while (1);

	return 0;
}
