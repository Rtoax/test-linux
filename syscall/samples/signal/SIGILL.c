#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

sigjmp_buf jmpbuf;

void sig_handler(int sig)
{
	switch (sig) {
	case SIGILL:
		printf("Catch SIGILL.\n");
		siglongjmp(jmpbuf, 1);
	default:
		break;
	}
	exit(1);
}

int main(int argc, char *argv[])
{
	int ret, savesigs;

	signal(SIGILL, sig_handler);

	/**
	 * If, and only if, the savesigs argument provided to sigsetjmp() is
	 * nonzero, the process's current signal mask is saved in env and
	 * will be restored if a siglongjmp() is later performed with this
	 * env.
	 */
	savesigs = 1;
	ret = sigsetjmp(jmpbuf, savesigs);
	(void)ret;

	/* Emulate Illegal instruction (core dumped) */
#if 0
	raise(SIGILL);
#else
	__asm__ __volatile__("ud2\n");
#endif

	return EXIT_SUCCESS;
}

