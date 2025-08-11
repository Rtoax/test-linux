#include <stdio.h>
#include <stdint.h>
#include <byteswap.h>

struct fp32 {
	unsigned int sign:1;
	unsigned int exponent:8;
	unsigned int mantissa:23;
} __attribute__((packed));

static struct fp32 fp32_NaN = {1, 255, 255};

void float_to_fp32(const float f)
{
	float tmp = f;
	int32_t *i32 = (int32_t *)&tmp;
	int32_t i32_orig = *i32;

	*i32 = bswap_32(*i32);
	struct fp32 *fp32 = (struct fp32 *)i32;

	printf("%10.2f : %08x : %08x : %-2d %-8d %-23d\n", f, *i32, i32_orig,
		fp32->sign, fp32->exponent, fp32->mantissa);
}

int main(void)
{
	int32_t *i32 = (int32_t *)&fp32_NaN;
	*i32 = bswap_32(*i32);

	float *f32 = (float *)i32;
	printf("%f\n", *f32);

	float_to_fp32(0.0f);
	float_to_fp32(1.0f);
	float_to_fp32(2.0f);
	float_to_fp32(4.0f);
	float_to_fp32(5.0f);
	float_to_fp32(-1.0f);
	float_to_fp32(-1024.0f);

	return 0;
}
