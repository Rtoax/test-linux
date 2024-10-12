#include <stdio.h>

int foo(void)
{
	/**
	 * getchar():
	 * - R_X86_64_GOTPCRELX in ELF 64-bit LSB relocatable if no PLT
	 */
	getchar();
	return 0;
}
