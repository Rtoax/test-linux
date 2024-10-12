#include <stdio.h>

int main(void)
{
	/**
	 * getchar():
	 * - R_X86_64_PLT32 in ELF 64-bit LSB relocatable if has PLT
	 * - R_X86_64_JUMP_SLOT in ELF 64-bit LSB executable if has PLT
	 * - R_X86_64_GOTPCRELX in ELF 64-bit LSB relocatable if no PLT
	 * - R_X86_64_GLOB_DAT in ELF 64-bit LSB executable if no PLT
	 */
	getchar();
	return 0;
}
