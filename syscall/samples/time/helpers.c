#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <sys/syscall.h>
#include "helpers.h"

int sys_clock_getres(clockid_t clockid, struct timespec *tp)
{
	return syscall(__NR_clock_getres, clockid, tp);
}

int sys_clock_gettime(clockid_t clockid, struct timespec *tp)
{
	return syscall(__NR_clock_gettime, clockid, tp);
}

int sys_nanosleep(const struct timespec *duration, struct timespec *rem)
{
	return syscall(__NR_nanosleep, duration, rem);
}

int nsec_to_ts(nsec_t ns, struct timespec *ts)
{
	if (ts == NULL) {
		printf("ERROR in %s: ts is NULL\n", __FUNCTION__);
		return 1;
	}
	ts->tv_sec = ns / NS_PER_SEC;
	ts->tv_nsec = ns % NS_PER_SEC;
	return 0;
}
