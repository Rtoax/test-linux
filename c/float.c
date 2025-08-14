/**
 * https://en.wikipedia.org/wiki/IEEE_754-2008_revision
 * https://en.wikipedia.org/wiki/Single-precision_floating-point_format
 */
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <byteswap.h>

struct fp32 {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	unsigned int mantissa:23;
	unsigned int exponent:8;
	unsigned int sign:1;
#define FP32(sign, exponent, mantissa) {mantissa, exponent, sign}
#else
	unsigned int sign:1;
	unsigned int exponent:8;
	unsigned int mantissa:23;
#define FP32(sign, exponent, mantissa) {sign, exponent, mantissa}
#endif
} __attribute__((packed));

static struct fp32 fp32_NaN = FP32(1, 255, 255);
static struct fp32 fp32_Zero = FP32(0, 0, 0);

void float_to_fp32(const float f)
{
	float tmp = f;
	int32_t i32 = *(int32_t *)&tmp;

	struct fp32 *fp32 = (struct fp32 *)&i32;

	printf("%20.5f : %08x : %-2d %-8d %-23d\n", f, i32,
		fp32->sign, fp32->exponent, fp32->mantissa);
}

float fp32_to_float(const struct fp32 *fp32)
{
	float f, cal_f;
	int32_t i32 = *(int32_t *)fp32;

	f = *(float *)&i32;

	float sign = 1 - 2 * (fp32->sign % 2);
	float e2, fra;

	if (fp32->exponent == 0) {
		e2 = exp2(-14);
		fra = fp32->mantissa / 1024;
	} else if (fp32->exponent == 0xff) {
		//if (fp32->mantissa = 0)
		// TODO: 0: +inf,-inf else NaN
	} else {
		e2 = exp2(fp32->exponent - 15);
		fra = 1 + fp32->mantissa / 1024;
	}

	// TODO: Wrong calculate
	cal_f = sign * e2 * fra;

	printf("%-2d %-8d %-23d : %10.5f(%.2f) : %08x\n",
		fp32->sign, fp32->exponent, fp32->mantissa, f, cal_f, i32);

	return cal_f;
}

int main(void)
{
	assert(sizeof(struct fp32) == 4);

	fp32_to_float(&fp32_NaN);
	fp32_to_float(&fp32_Zero);

	/* see https://en.wikipedia.org/wiki/Single-precision_floating-point_format */
	struct fp32 fp32_0dot15625 = FP32(0, 0x7c, 0x200000);
	fp32_to_float(&fp32_0dot15625);

	float_to_fp32(0.0f);
	float_to_fp32(1.0f);
	float_to_fp32(2.0f);
	float_to_fp32(4.0f);
	float_to_fp32(5.0f);
	float_to_fp32(-1.0f);
	float_to_fp32(-1024.0f);
	float_to_fp32(1.0f / 3);
	float_to_fp32(0.15625f);

	return 0;
}
