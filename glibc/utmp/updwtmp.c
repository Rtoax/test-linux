#include <stdio.h>
#include <utmp.h>
#include "utmp_helpers.h"

int main(void)
{
	struct utmp *utmp = getutent();

	print_utmp(utmp);

	updwtmp("/home/rongtao/wtmp.out", utmp);

	return 0;
}
