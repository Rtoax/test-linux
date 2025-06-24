#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#if defined(__x86_64__) || defined(__i386__)
# define BREAKPOINT()	asm volatile("int3")
#elif defined(__aarch64__)
# define BREAKPOINT()	asm volatile("brk #0")
#endif

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
