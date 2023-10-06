/**
 * Module Specific Register - MSR
 * https://stackoverflow.com/questions/64864035/any-cpuid-like-instruction-in-armv8
 */
#include <stdio.h>
#include <stdint.h>
#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>

sigjmp_buf go_here;

void sigill_handler(int signum) {
	(void)signum;
	siglongjmp(go_here, 1);
}

#define PRINT_REG(s)                                          \
	do {                                                  \
		if (sigsetjmp(go_here, 1)) {                  \
			printf("%s:\tSIGILL\n", s);           \
		} else {                                      \
			unsigned long ret;                    \
			asm("mrs %0, " s : "=r" (ret));       \
			printf("%s:\t%#lx\n", s, ret);        \
		}                                             \
	} while (0)

int main(void)
{
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigill_handler;
	if (sigaction(SIGILL, &sa, NULL) < 0) {
		perror("sigaction");
		exit(2);
	}
	
	PRINT_REG("MIDR_EL1");
	PRINT_REG("VPIDR_EL2");
	PRINT_REG("REVIDR_EL1");
	PRINT_REG("ID_AA64ISAR0_EL1");
	PRINT_REG("ID_AA64ISAR1_EL1");
	PRINT_REG("MVFR0_EL1");
	PRINT_REG("MVFR1_EL1");
	PRINT_REG("MVFR2_EL1");
	return 0;
}
