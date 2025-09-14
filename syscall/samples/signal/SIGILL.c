#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

#define JMP_RET	1
sigjmp_buf jmpbuf;

void sig_handler(int sig)
{
	switch (sig) {
	case SIGILL:
		printf("Catch SIGILL.\n");
		siglongjmp(jmpbuf, JMP_RET);
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
	if (ret == JMP_RET)
		return EXIT_FAILURE;

	/* Emulate Illegal instruction (core dumped) */
#if defined(__x86_64__)
	__asm__ __volatile__("ud2\n");
#elif defined(__aarch64__)
	/**
	 * See test-linux/insn/examples/invalid_opcode.h
	 */
	//__asm__ __volatile__("udf #0\n");
	__asm__ __volatile__(".word 0xdeadbeef\n");
#else
	raise(SIGILL);
#endif

	return EXIT_SUCCESS;
}

