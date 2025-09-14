#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <immintrin.h>


unsigned int rdrand32(void)
{
	unsigned int value;
	__asm__("rdrand  %[value]"
		: [value] "=r" (value)
		: /* no inputs */
		: "cc" /* clobbers flags (condition codes) */
		);
	return value;
}

int main(void)
{
	long long unsigned int rand;
	uint32_t rand32;

	rand32 = rdrand32();
	printf("rand = %d\n", rand32);

	/**
	 * Intel C/C++ Compiler Intrinsic Equivalent
	 */
	_rdrand64_step(&rand);

	return 0;
}
