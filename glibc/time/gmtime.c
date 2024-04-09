#include <stdio.h>
#include <time.h>


int main(void)
{
	time_t time = 1;
	struct tm *t = gmtime(&time);
	struct tm *t2, rslt;
	t2 = gmtime_r(&time, &rslt);

	printf("tm_sec = %d:%d\n", t->tm_sec, t2->tm_sec);
	printf("tm_min = %d:%d\n", t->tm_min, t2->tm_min);
	printf("tm_hour = %d:%d\n", t->tm_hour, t2->tm_hour);
	printf("tm_mday = %d:%d\n", t->tm_mday, t2->tm_mday);
	printf("tm_mon = %d:%d\n", t->tm_mon, t2->tm_mon);
	printf("tm_year = %d:%d\n", t->tm_year, t2->tm_year);
	printf("tm_wday = %d:%d\n", t->tm_wday, t2->tm_wday);
	printf("tm_yday = %d:%d\n", t->tm_yday, t2->tm_yday);
	printf("tm_isdst = %d:%d\n", t->tm_isdst, t2->tm_isdst);
	printf("tm_gmtoff = %ld:%ld\n", t->tm_gmtoff, t2->tm_gmtoff);
	printf("tm_zone = %s:%s\n", t->tm_zone, t2->tm_zone);

	return 0;
}
