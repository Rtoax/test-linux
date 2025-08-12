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
	int32_t i32 = *(int32_t *)&tmp;
	int32_t i32_orig = i32;

	i32 = bswap_32(i32);
	struct fp32 *fp32 = (struct fp32 *)&i32;

	printf("%10.2f : %08x : %08x : %-2d %-8d %-23d\n", f, i32, i32_orig,
		fp32->sign, fp32->exponent, fp32->mantissa);
}

void fp32_to_float(const struct fp32 *fp32)
{
	float f;
	int32_t i32 = *(int32_t *)fp32;
	int32_t i32_orig = i32;

	i32 = bswap_32(i32);
	f = *(float *)&i32;

	printf("%-2d %-8d %-23d : %10.2f : %08x : %08x\n",
		fp32->sign, fp32->exponent, fp32->mantissa, f, i32, i32_orig);
}

int main(void)
{
	fp32_to_float(&fp32_NaN);

	float_to_fp32(0.0f);
	float_to_fp32(1.0f);
	float_to_fp32(2.0f);
	float_to_fp32(4.0f);
	float_to_fp32(5.0f);
	float_to_fp32(-1.0f);
	float_to_fp32(-1024.0f);
	float_to_fp32(1.0f / 3);

	return 0;
}
