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
	unsigned int fraction:23;
	unsigned int exponent:8;
	unsigned int sign:1;
#define FP32(sign, exponent, fraction) {fraction, exponent, sign}
#else
	unsigned int sign:1;
	unsigned int exponent:8;
	unsigned int fraction:23;
#define FP32(sign, exponent, fraction) {sign, exponent, fraction}
#endif
} __attribute__((packed));

const struct fp32 fp32_NaN = FP32(1, 255, 255);
const struct fp32 fp32_Inf = FP32(1, 255, 0);
const struct fp32 fp32_Zero = FP32(0, 0, 0);
/* see https://en.wikipedia.org/wiki/Single-precision_floating-point_format */
const struct fp32 fp32_0dot15625 = FP32(0, 0x7c, 0x200000);

void float_to_fp32(const float f, struct fp32 *fp32)
{
	float tmp = f;
	int32_t i32 = *(int32_t *)&tmp;

	*fp32 = *(struct fp32 *)&i32;

#ifdef DEBUG
	printf("%20.5f : %08x : %-2d %-8d %-23d\n", f, i32,
		fp32->sign, fp32->exponent, fp32->fraction);
#endif
}

float fp32_to_float(const struct fp32 *fp32)
{
	int i;
	float f, cal_f;
	int32_t i32 = *(int32_t *)fp32;

	f = *(float *)&i32;
	(void)f;

	float sign = 1 - 2 * (fp32->sign % 2);
	float e2, fra;

	if (fp32->exponent == 0) {
		if (fp32->fraction == 0) {
			cal_f = sign * 0.0f;
			goto skip_cal;
		} else {
			e2 = exp2(-126);
			fra = 0;
			for (i = 1; i <= 23; i++) {
				unsigned int tmp = fp32->fraction >> (23 - i) & 0x1;
				if (tmp == 0)
					continue;
				fra += exp2(-i);
			}
		}
	} else if (fp32->exponent == 0xff) {
		if (fp32->fraction == 0)
			cal_f = sign * *(float *)&fp32_Inf;
		else
			cal_f = *(float *)&fp32_NaN;
		goto skip_cal;
	} else {
		e2 = exp2(fp32->exponent - 127);
		fra = 1;
		for (i = 1; i <= 23; i++) {
			unsigned int tmp = fp32->fraction >> (23 - i) & 0x1;
			if (tmp == 0)
				continue;
			fra += exp2(-i);
		}
	}

	cal_f = sign * e2 * fra;

skip_cal:
#ifdef DEBUG
	printf("%-1x %-2x %-6x : %10.5f(%10.5f) : %08x\n",
		fp32->sign, fp32->exponent, fp32->fraction, f, cal_f, i32);
#endif
	return cal_f;
}

void check_fp32(float f)
{
	float to;
	struct fp32 fp32;

	float_to_fp32(f, &fp32);
	to = fp32_to_float(&fp32);

	printf("%f vs %f\n", f, to);
}

int main(void)
{
	assert(sizeof(struct fp32) == 4);

	check_fp32(0);
	check_fp32(1.2f);
	check_fp32(0.2f);
	check_fp32(3.14159265f);
	check_fp32(-3.14159265f);

	return 0;
}
