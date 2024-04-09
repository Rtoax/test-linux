#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t time = 100000;
	struct tm *t = gmtime(&time);
	time_t time2 = mktime(t);
	printf("time2: %ld\n", time2);

	return 0;
}
