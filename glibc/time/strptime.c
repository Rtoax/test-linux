#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif
#include <stdio.h>
#include <time.h>
#include <string.h>


int main(void)
{
	struct tm t4, *tp;
	tp = &t4;
	memset(&t4, 0, sizeof(t4));
	strptime("335-19:01:43", "%j-%H:%M:%S\n", &t4);

	printf("tm_sec = %d:%d\n", tp->tm_sec, t4.tm_sec);
	printf("tm_min = %d:%d\n", tp->tm_min, t4.tm_min);
	printf("tm_hour = %d:%d\n", tp->tm_hour, t4.tm_hour);
	printf("tm_mday = %d:%d\n", tp->tm_mday, t4.tm_mday);
	printf("tm_mon = %d:%d\n", tp->tm_mon, t4.tm_mon);
	printf("tm_year = %d:%d\n", tp->tm_year, t4.tm_year);
	printf("tm_wday = %d:%d\n", tp->tm_wday, t4.tm_wday);
	printf("tm_yday = %d:%d\n", tp->tm_yday, t4.tm_yday);
	printf("tm_isdst = %d:%d\n", tp->tm_isdst, t4.tm_isdst);

	return 0;
}
