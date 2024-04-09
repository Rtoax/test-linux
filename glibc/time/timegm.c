#include <stdio.h>
#include <time.h>
#include "helpers.h"

int main(void)
{
	time_t time = 19;
	struct tm *t2, rslt;
	t2 = gmtime_r(&time, &rslt);

	print_tm(t2);

	time = timegm(t2);
	printf("time: %ld\n", time);

	return 0;
}
