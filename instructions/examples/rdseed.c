#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <immintrin.h>


int main(void)
{
	uint32_t seed32;

	_rdseed32_step(&seed32);
	printf("seed = %ld\n", seed32);

	return 0;
}
