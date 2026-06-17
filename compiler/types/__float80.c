/**
 * __float80 is available on the i386, x86_64, and IA-64 targets, and supports
 * the 80-bit (XFmode) floating type. It is an alias for the type name _Float64x
 * on these targets.
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>

#define PI 3.14159265358979323846264338327950288419716939937510

/**
 * Assuming FP64 is an accurate value, calculate the floating-point precision
 * error of FP16.
 *
 * TODO: do not use fp64, use fp128 as accurate value.
 */
void precision_error(void)
{
	double fp64 = PI;
	__float80 fp80 = (__float80)PI;

	double res_mul_fp64 = fp64 * fp64;
	__float80 res_mul_fp80 = fp80 * fp80;

	double res_add_fp64 = fp64 + fp64;
	__float80 res_add_fp80 = fp80 + fp80;

	double err_add = fabs(res_add_fp64 - (double)res_add_fp80);
	double err_mul = fabs(res_mul_fp64 - (double)res_mul_fp80);

	printf("FP64 Reference Add: %.17f\n", res_add_fp64);
	printf("CPU FP16 Test Add:  %.17f\n", (double)res_add_fp80);
	printf("Absolute Error Add: %e\n\n", err_add);

	printf("FP64 Reference Mul: %.17f\n", res_mul_fp64);
	printf("CPU FP16 Test Mul:  %.17f\n", (double)res_mul_fp80);
	printf("Absolute Error Mul: %e\n\n", err_mul);
}

int main(void)
{
	assert(sizeof(__float80) == 16 &&
	       "size of __float80 is not equal to 16");

	__float80 f80 = PI;
	_Float64x f64x = PI;

	printf("size of __float80 %ld\n", sizeof(f80));
	printf("size of _Float64x %ld\n", sizeof(f64x));

	precision_error();

	return 0;
}
