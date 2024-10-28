/**
 * R_X86_64_PLT32: 32 bit PLT address
 */
#include <stdio.h>

extern void bar(void);

int foo(void)
{
	char buf[32];

	buf[0] = 'H';
	buf[1] = 'e';
	buf[2] = 'l';
	buf[3] = 'l';
	buf[4] = 'o';
	buf[5] = '\0';

	/**
	 * puts():
	 * R_X86_64_PLT32 in ELF 64-bit LSB relocatable if has PLT,
	 * and it's could becomes R_X86_64_JUMP_SLOT in ELF 64-bit LSB
	 * executable if has PLT.
	 */
	puts(buf);

	/**
	 * bar is R_X86_64_PLT32 in ELF 64-bit LSB relocatable
	 */
	bar();

	return 0;
}
