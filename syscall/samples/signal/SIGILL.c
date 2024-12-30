#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


void sig_handler(int sig)
{
	switch (sig) {
	case SIGILL:
		printf("Catch SIGILL.\n");
	default:
		break;
	}
	exit(1);
}

int main(int argc, char *argv[])
{
	signal(SIGILL, sig_handler);

	/* Emulate Illegal instruction (core dumped) */
#if 0
	raise(SIGILL);
#else
	__asm__ __volatile__("ud2\n");
#endif

	return EXIT_SUCCESS;
}

