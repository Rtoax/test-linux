/**
 * __float80 is available on the i386, x86_64, and IA-64 targets, and supports
 * the 80-bit (XFmode) floating type. It is an alias for the type name _Float64x
 * on these targets.
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include "__float128.h"

#define PI100 \
	3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
#define PI100Q \
	3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679Q

void base(void)
{
	assert(sizeof(__float80) == 16 &&
	       "size of __float80 is not equal to 16");

	__float80 f80 = PI100;
	_Float64x f64x = PI100;

	printf("size of __float80 %ld\n", sizeof(f80));
	printf("size of _Float64x %ld\n", sizeof(f64x));
}

/**
 * Assuming FP128 is an accurate value, calculate the floating-point precision
 * error of FP80.
 */
void precision_error(void)
{
#ifdef SUPPORT___float128
	__float128 fp128 = PI100Q;
	__float80 fp80 = (__float80)PI100;

	__float128 res_mul_fp128 = fp128 * fp128;
	__float80 res_mul_fp80 = fp80 * fp80;

	__float128 res_add_fp128 = fp128 + fp128;
	__float80 res_add_fp80 = fp80 + fp80;

	__float128 err_add = fabsq(res_add_fp128 - (__float128)res_add_fp80);
	__float128 err_mul = fabsq(res_mul_fp128 - (__float128)res_mul_fp80);

	printf("FP128 Reference Add: ");
	fp128_printf(res_add_fp128, "%.35Qf");
	printf("CPU FP80 Test Add:  %.17Lf\n", res_add_fp80);
	printf("Absolute Error Add: ");
	fp128_printf(err_add, "%.35Qf");

	printf("FP128 Reference Mul: ");
	fp128_printf(res_mul_fp128, "%.35Qf");
	printf("CPU FP80 Test Mul:  %.17Lf\n", res_mul_fp80);
	printf("Absolute Error Mul: ");
	fp128_printf(err_mul, "%.35Qf");
#endif
}

int main(void)
{
	base();
	precision_error();

	return 0;
}
