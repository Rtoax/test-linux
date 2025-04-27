#include <stdio.h>
#include <sys/resource.h>
#include <malloc.h>
#include <unistd.h>

#include "resource_helpers.h"

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

void memory(void)
{
	int i, pagesize;
	int size = 1024 * 1024 * 1024;
	char *mem;
	struct rusage rusage;

	pagesize = getpagesize();

	getrusage(RUSAGE_SELF, &rusage);
	print_rusage("BEFORE: ", &rusage);

	mem = malloc(size);
	for (i = 0; i < size; i += pagesize)
		mem[i] = 'A';

	getrusage(RUSAGE_SELF, &rusage);
	print_rusage("AFTER: ", &rusage);

	free(mem);
}

int main(void)
{
	user_sys();
	memory();

	return 0;
}

