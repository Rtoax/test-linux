/**
 * R_X86_64_PLT32: 32 bit PLT address
 */
#include <stdio.h>

int foo(void)
{
	/**
	 * getchar():
	 * R_X86_64_PLT32 in ELF 64-bit LSB relocatable if has PLT,
	 * and it's could becomes R_X86_64_JUMP_SLOT in ELF 64-bit LSB
	 * executable if has PLT.
	 */
	getchar();
	return 0;
}
