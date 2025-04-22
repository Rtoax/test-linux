/**
 * R_AARCH64_CALL26: 32 Likewise for CALL
 */
#include <stdio.h>

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
	return 0;
}
