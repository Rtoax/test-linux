#include <stdio.h>
#include <stdint.h>
#include <byteswap.h>

struct fp32 {
	int sign:1;
	int exponent:8;
	int mantissa:23;
} __attribute__((packed));

int main(void)
{
	struct fp32 fp32_Inf = {1, 255, 255};

	int32_t *i32 = (int32_t *)&fp32_Inf;
	bswap_32(*i32);

	float *f32 = (float *)i32;
	printf("%f\n", *f32);
	return 0;
}
