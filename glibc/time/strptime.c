#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "time_helpers.h"


int main(void)
{
	struct tm t4, *tp;
	tp = &t4;
	memset(&t4, 0, sizeof(t4));
	strptime("335-19:01:43", "%j-%H:%M:%S\n", &t4);

	print_tm(tp);
	print_tm(&t4);

	return 0;
}
