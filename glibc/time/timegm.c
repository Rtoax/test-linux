#include <stdio.h>
#include <time.h>


int main(void)
{
	time_t time = 19;
	struct tm *t2, rslt;
	t2 = gmtime_r(&time, &rslt);
	time_t time2 = timegm(t2);
	printf("time2: %ld\n", time2);

	return 0;
}
