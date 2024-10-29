/**
 * R_X86_64_COPY: value = 5, field = none,  calculation = none
 */

#include <stdio.h>

int main(void)
{
	/**
	 * stderr is R_X86_64_COPY in ELF 64-bit LSB executable
	 */
	fprintf(stderr, "hello\n");
	return 0;
}
