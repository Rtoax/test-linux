#include <stdio.h>

int main(void)
{
	/**
	 * getchar():
	 * R_X86_64_GLOB_DAT in ELF 64-bit LSB executable if no PLT
	 * and it's could be R_X86_64_GOTPCRELX in ELF 64-bit LSB relocatable
	 * if no PLT before link.
	 */
	getchar();
	return 0;
}
