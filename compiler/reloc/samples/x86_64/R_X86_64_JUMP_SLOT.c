/**
 * R_X86_64_JUMP_SLOT: Create PLT entry
 */
#include <stdio.h>

int main(void)
{
	/**
	 * getchar():
	 * R_X86_64_JUMP_SLOT in ELF 64-bit LSB executable if has PLT,
	 * and it's could be R_X86_64_PLT32 in ELF 64-bit LSB relocatable if
	 * has PLT before link.
	 */
	getchar();
	return 0;
}
