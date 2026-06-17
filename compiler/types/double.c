#include <math.h>
#include <stdio.h>
#include "__float128.h"

#define PI100 \
	3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986264348253421170679
#define PI100Q \
	3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679Q

void base(void)
{
	double f64 = PI100;
	printf("%.64f\n", (double)f64);
}

/**
 * Assuming FP128 is an accurate value, calculate the floating-point precision
 * error of FP64.
 */
void precision_error(void)
{
#ifdef SUPPORT___float128
	__float128 fp128 = PI100Q;
	double fp64 = (double)PI100;

	__float128 res_mul_fp128 = fp128 * fp128;
	double res_mul_fp64 = fp64 * fp64;

	__float128 res_add_fp128 = fp128 + fp128;
	double res_add_fp64 = fp64 + fp64;

	__float128 err_add = fabsq(res_add_fp128 - (__float128)res_add_fp64);
	__float128 err_mul = fabsq(res_mul_fp128 - (__float128)res_mul_fp64);

	printf("FP128 Reference Add: ");
	fp128_printf(res_add_fp128, "%.35Qf");
	printf("CPU FP64 Test Add:  %.17f\n", res_add_fp64);
	printf("Absolute Error Add: ");
	fp128_printf(err_add, "%.35Qf");

	printf("FP128 Reference Mul: ");
	fp128_printf(res_mul_fp128, "%.35Qf");
	printf("CPU FP64 Test Mul:  %.17f\n", res_mul_fp64);
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
