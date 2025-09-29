#include <stdio.h>
#include <stdint.h>

__bf16 __floattobf16(float fp32)
{
	uint32_t float_bits = *(uint32_t *)&fp32;
	uint16_t bf16_bits = (uint16_t)(float_bits >> 16);
	__bf16 *bf16 = (__bf16 *)&bf16_bits;
	return *bf16;
}

float __bf16tofloat(__bf16 bf16)
{
	uint16_t bf16_bits = *(uint16_t *)&bf16;
	uint32_t float_bits = (uint32_t)(bf16_bits << 16);
	float fp32 = *(float *)&float_bits;
	return fp32;
}

int main(void)
{
	__bf16 b = __floattobf16(-3.141592653f);
	__bf16 c = b;
	printf("%f\n", __bf16tofloat(c));
	return 0;
}
