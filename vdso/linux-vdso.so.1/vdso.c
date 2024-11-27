#include <stdio.h>

#include "vdso.h"

int my_clock_gettime(clockid_t clockid, struct timespec *res)
{
	return printf("I am clock_gettime from custom vdso.\n");
}
