#include <time.h>
#include <stdio.h>
#include "time_helpers.h"

void rt_nanosleep(nsec_t ns)
{
	struct timespec ts_sleep, ts_rem;
	int rc;
	nsec_to_ts(ns, &ts_sleep);
	rc = clock_nanosleep(CLOCK_MONOTONIC, 0, &ts_sleep, &ts_rem);
	if (rc != 0)
		printf("WARNING: rt_nanosleep() returned early by %d s %d ns\n",
		       (int)ts_rem.tv_sec, (int)ts_rem.tv_nsec);
}

int main(void)
{
	int i;
	for (i = 0; i < 10; i++) {
		rt_nanosleep(100000000);
		printf("rt_nanosleep\n");
	}
	return 0;
}
