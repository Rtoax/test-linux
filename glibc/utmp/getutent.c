#include <stdio.h>
#include <utmp.h>
#include "helpers.h"

int main(void)
{
	struct utmp *utmp = getutent();

	print_utmp(utmp);

	setutent();

	struct utmp *ut = getutid(utmp);
	print_utmp(ut);

	endutent();

	return 0;
}
