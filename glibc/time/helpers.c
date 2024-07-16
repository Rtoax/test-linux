#include <stdio.h>
#include <time.h>
#include <errno.h>

#include "helpers.h"


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
