/**
 * R_AARCH64_CALL26: 32 Likewise for CALL (link R_X86_64_PLT32)
 */
#include <stdio.h>

/* R_AARCH64_PREL32 */
void foo(void) {}

/* R_AARCH64_PREL32 */
int main(void)
{
	char buf[32];

	buf[0] = 'H';
	buf[1] = 'e';
	buf[2] = 'l';
	buf[3] = 'l';
	buf[4] = 'o';
	buf[5] = '\0';

	/**
	 * puts is R_AARCH64_CALL26 in relocation elf file
	 * puts is R_AARCH64_JUMP_SLOT in execute elf file.
	 */
	puts(buf);

	/**
	 * foo is R_AARCH64_CALL26 in relocation elf file.
	 */
	foo();

	return 0;
}
