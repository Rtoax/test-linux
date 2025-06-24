#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <immintrin.h>
#include <x86intrin.h>


unsigned int rdseed32(void)
{
	unsigned int value;
	__asm__("rdseed  %[value]"
		: [value] "=r" (value)
		: /* no inputs */
		: "cc" /* clobbers flags (condition codes) */
		);
	return value;
}

int main(void)
{
	uint32_t seed32;

	_rdseed32_step(&seed32);
	printf("seed = %d\n", seed32);

	seed32 = rdseed32();
	printf("seed = %d\n", seed32);

	return 0;
}
