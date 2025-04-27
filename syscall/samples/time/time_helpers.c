#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <sys/syscall.h>
#include <errno.h>
#include <time.h>
#include "time_helpers.h"


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

int print_tm(struct tm *tm)
{
	if (!tm)
		return -EINVAL;

	printf("tm_sec = %d\n", tm->tm_sec);
	printf("tm_min = %d\n", tm->tm_min);
	printf("tm_hour = %d\n", tm->tm_hour);
	printf("tm_mday = %d\n", tm->tm_mday);
	printf("tm_mon = %d\n", tm->tm_mon);
	printf("tm_year = %d\n", tm->tm_year);
	printf("tm_wday = %d\n", tm->tm_wday);
	printf("tm_yday = %d\n", tm->tm_yday);
	printf("tm_isdst = %d\n", tm->tm_isdst);
	printf("tm_gmtoff = %ld\n", tm->tm_gmtoff);
	printf("tm_zone = %s\n", tm->tm_zone);

	return 0;
}
