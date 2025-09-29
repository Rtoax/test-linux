#include <stdio.h>
#include <stdint.h>

#define DIRECT_CONVERT	1

__bf16 __floattobf16(float fp32)
{
#ifdef DIRECT_CONVERT
	return fp32;
#else
	uint32_t float_bits = *(uint32_t *)&fp32;
	uint16_t bf16_bits = (uint16_t)(float_bits >> 16);
	__bf16 *bf16 = (__bf16 *)&bf16_bits;
	return *bf16;
#endif
}

float __bf16tofloat(__bf16 bf16)
{
#ifdef DIRECT_CONVERT
	return bf16;
#else
	uint16_t bf16_bits = *(uint16_t *)&bf16;
	uint32_t float_bits = (uint32_t)(bf16_bits << 16);
	float fp32 = *(float *)&float_bits;
	return fp32;
#endif
}

int main(void)
{
	__bf16 b = __floattobf16(-3.141592653f);
	__bf16 c = b;
	printf("%f\n", __bf16tofloat(c));
	return 0;
}
