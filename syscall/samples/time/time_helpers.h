#pragma once

#include <time.h>

#define NS_PER_MS 1000000
#define NS_PER_US 1000
#define NS_PER_SEC 1000000000
#define US_PER_MS 1000
#define US_PER_SEC 1000000
#define MS_PER_SEC 1000

typedef unsigned long long nsec_t;

int sys_clock_getres(clockid_t clockid, struct timespec *tp);
int sys_clock_gettime(clockid_t clockid, struct timespec *tp);
int sys_nanosleep(const struct timespec *duration, struct timespec *rem);

int nsec_to_ts(nsec_t ns, struct timespec *ts);

int print_tm(struct tm *tm);
