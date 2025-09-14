/**
 * Module Specific Register - MSR
 * https://stackoverflow.com/questions/64864035/any-cpuid-like-instruction-in-armv8
 */
#include <stdio.h>
#include <stdint.h>
#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>
#include <inttypes.h>

sigjmp_buf go_here;

void sigill_handler(int signum) {
	(void)signum;
	siglongjmp(go_here, 1);
}

#define GET_REG(s) ({                                         \
		unsigned long ___r = 0UL;                     \
		if (sigsetjmp(go_here, 1)) {                  \
			printf("%s:\tSIGILL\n", s);           \
		} else {                                      \
			asm("mrs %0, " s : "=r" (___r));      \
			printf("%s:\t%#lx\n", s, ___r);       \
		}                                             \
		___r;                                         \
	})

int main(void)
{
	unsigned long val;

	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigill_handler;
	if (sigaction(SIGILL, &sa, NULL) < 0) {
		perror("sigaction");
		exit(2);
	}

	val = GET_REG("CurrentEL");
	val = GET_REG("MIDR_EL1");
	val = GET_REG("VPIDR_EL2");
	val = GET_REG("REVIDR_EL1");
	val = GET_REG("SCTLR_EL1");
	val = GET_REG("TCR_EL1");
	val = GET_REG("ID_AA64ISAR0_EL1");
	printf("ID_AA64ISAR0_EL1.DP:\t0x%" PRIX64 "(asimdd)\n", (val >> 44) & 0xF);
	val = GET_REG("ID_AA64ISAR1_EL1");
	val = GET_REG("ID_AA64MMFR0_EL1");
	val = GET_REG("ID_AA64MMFR1_EL1");
	val = GET_REG("ID_AA64PFR0_EL1");
	printf("ID_AA64PFR0_EL1.EL0:\t0x%" PRIX64 "\n", val & 0xF);
	printf("ID_AA64PFR0_EL1.EL1:\t0x%" PRIX64 "\n", (val >> 4) & 0xF);
	printf("ID_AA64PFR0_EL1.EL2:\t0x%" PRIX64 "\n", (val >> 8) & 0xF);
	printf("ID_AA64PFR0_EL1.SVE:\t0x%" PRIX64 "(sve)\n", (val >> 32) & 0xF);
#if defined(CPU_HAVE_SVE) || defined(CPU_HAVE_SVE2)
	//val = GET_REG("ZCR_EL1");
#endif
	val = GET_REG("ID_AA64PFR1_EL1");
	val = GET_REG("ID_AA64DFR0_EL1");
	val = GET_REG("ID_AA64DFR1_EL1");
	val = GET_REG("MVFR0_EL1");
	val = GET_REG("MVFR1_EL1");
	val = GET_REG("MVFR2_EL1");
	val = GET_REG("TTBR0_EL1");
	val = GET_REG("TTBR1_EL1");

	val = GET_REG("HCR_EL2");
	printf("HCR_EL2:\t0x%" PRIX64 "\n", val);

	return 0;
}
