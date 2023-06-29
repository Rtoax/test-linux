#include <stdio.h>

int main(void)
{
	unsigned long crc, val;

	/* FIXME: Error: number of operands mismatch for `crc32' */
	//__asm__ volatile("crc32b %w0, %w0, %w1" : "+r"(crc) : "r"(val));

	return 0;
}
