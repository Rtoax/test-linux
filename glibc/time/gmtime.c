#include <stdio.h>
#include <time.h>
#include "time_helpers.h"

int main(void)
{
	time_t time = 1;
	struct tm *t = gmtime(&time);
	struct tm *t2, rslt;
	t2 = gmtime_r(&time, &rslt);

	print_tm(t);
	print_tm(t2);

	return 0;
}
