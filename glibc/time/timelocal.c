#include <stdio.h>
#include <time.h>
#include <sys/timex.h>

int main(void)
{
	struct tm *t2, rslt;
	time_t time = 1999999;
	time_t time2;

	t2 = localtime_r(&time, &rslt);

	time2 = timelocal(t2);
	printf("time2: %ld\n", time2);

	return 0;
}
