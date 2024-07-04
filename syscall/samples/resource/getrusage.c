#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

#include "helpers.h"

void user_sys(void)
{
	struct rusage rsue, rsue2;
	float user, sys;

	getrusage(getpid(), &rsue);
	usleep(100);
	getrusage(getpid(), &rsue2);

	user = (float)rsue.ru_utime.tv_sec + rsue.ru_utime.tv_usec / 1000000.0;
	user += (float)rsue2.ru_utime.tv_sec + rsue2.ru_utime.tv_usec / 1000000.0;

	sys = (float)rsue.ru_stime.tv_sec + rsue.ru_stime.tv_usec / 1000000.0;
	sys += (float)rsue2.ru_stime.tv_sec + rsue2.ru_stime.tv_usec / 1000000.0;

	/* FIXME: wrong value i think */
	printf("user: %g, sys time: %g\n", user, sys);
}

int main(void)
{
	struct rusage rusage;

	getrusage(RUSAGE_SELF, &rusage);
	print_rusage(&rusage);

	user_sys();

	return 0;
}

