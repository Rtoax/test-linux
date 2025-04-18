#pragma once
#include <time.h>
#include <sys/time.h>

#if defined(__x86_64__) || defined(__i386__) || defined(__arm__)
#define vdso_clock_gettime	__vdso_clock_gettime
#define vdso_gettimeofday	__vdso_gettimeofday
#elif defined(__aarch64__)
#define vdso_clock_gettime	__kernel_clock_gettime
#define vdso_gettimeofday	__kernel_gettimeofday
#endif

int vdso_clock_gettime(clockid_t clockid, struct timespec *res);
int vdso_gettimeofday(struct timeval *tv, struct timezone *tz);
