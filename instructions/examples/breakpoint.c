#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "breakpoint.h"

static char *prog = NULL;

void sigtrap(int sig)
{
	printf("Get SIGTRAP.\n");
}

int trap(void)
{
	BREAKPOINT();
	return 0;
}

void usage(void)
{
	fprintf(stderr, "Usage: %s [sig]\n", prog);
}

int main(int argc, char *argv[])
{
	prog = argv[0];

	if (argc > 1) {
		if (strcmp(argv[1], "sig")) {
			usage();
			exit(1);
		}
		signal(SIGTRAP, sigtrap);
	}
	usage();

	trap();

	return 0;
}
