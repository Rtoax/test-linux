#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846264338327950288419716939937510

void base(void)
{
	_Float16 f16 = (_Float16)PI;
	printf("%.17f\n", (float)f16);
}

/**
 * Assuming FP64 is an accurate value, calculate the floating-point precision
 * error of FP16.
 *
 * see also test-linux/hpc/nvidia/cuda/intrinsics/half.cu
 */
void precision_error(void)
{
	double fp64 = PI;
	_Float16 fp16 = (_Float16)PI;

	double res_mul_fp64 = fp64 * fp64;
	_Float16 res_mul_fp16 = fp16 * fp16;

	double res_add_fp64 = fp64 + fp64;
	_Float16 res_add_fp16 = fp16 + fp16;

	double err_add = fabs(res_add_fp64 - (double)res_add_fp16);
	double err_mul = fabs(res_mul_fp64 - (double)res_mul_fp16);

	printf("FP64 Reference Add: %.17f\n", res_add_fp64);
	printf("CPU FP16 Test Add:  %.17f\n", (double)res_add_fp16);
	printf("Absolute Error Add: %e\n\n", err_add);

	printf("FP64 Reference Mul: %.17f\n", res_mul_fp64);
	printf("CPU FP16 Test Mul:  %.17f\n", (double)res_mul_fp16);
	printf("Absolute Error Mul: %e\n\n", err_mul);
}

int main(void)
{
	base();
	precision_error();
	return 0;
}
