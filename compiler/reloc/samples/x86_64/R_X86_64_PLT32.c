/**
 * R_X86_64_PLT32: 32 bit PLT address (like R_AARCH64_CALL26)
 */
#include <stdio.h>

/* R_X86_64_PC32 in ELF 64-bit LSB relocatable */
void bar(void)
{
}

/* R_X86_64_PC32 in ELF 64-bit LSB relocatable */
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

/* R_X86_64_PC32 in ELF 64-bit LSB relocatable */
int main(void)
{
	return 0;
}
