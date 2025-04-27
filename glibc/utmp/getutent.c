#include <stdio.h>
#include <utmp.h>
#include "utmp_helpers.h"

int main(void)
{
	struct utmp *utmp = getutent();

	print_utmp(utmp);

	setutent();

	struct utmp *ut = getutid(utmp);
	print_utmp(ut);

	struct utmp *ut2 = getutline(ut);
	print_utmp(ut2);

	struct utmp *ut3 = pututline(ut2);
	if (!ut3) {
		fprintf(stderr, "pututline() %m\n");
	}
	print_utmp(ut3);

	endutent();

	return 0;
}
