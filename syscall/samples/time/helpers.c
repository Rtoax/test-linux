#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
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
