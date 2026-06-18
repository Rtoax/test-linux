/**
 * This source code be included in test-linux/hpc/nvidia/cuda/intrinsics/float.cu
 */
#include <math.h>
#include <stdio.h>

#if defined(__NVCC__) || defined(__HPCC__) || defined(__LUCA__)
#define _CUDA_NVCC_COMPAT_COMPILER 1
#else
#define __global__
#endif

#ifndef PI
#define PI 3.14159265358979323846264338327950288419716939937510
#endif

void base(void)
{
	float f32 = (float)PI;
	printf("%.17f\n", (float)f32);
}

/**
 * Assuming FP64 is an accurate value, calculate the floating-point precision
 * error of FP32.
 */
__global__ void precision_error(void)
{
	double fp64 = PI;
	double res_mul_fp64 = fp64;
	double res_add_fp64 = fp64;
	double res_muladd_fp64 = fp64;

	float fp32 = (float)PI;
	float res_mul_fp32 = fp32;
	float res_add_fp32 = fp32;
	float res_muladd_fp32 = fp32;

	for (int i = 0; i < 20; i++) {
		res_mul_fp64 *= fp64;
		res_mul_fp32 *= fp32;
	}

	for (int i = 0; i < 10000000; i++) {
		res_add_fp64 += fp64;
		res_add_fp32 += fp32;
	}

	for (int i = 0; i < 21; i++) {
		res_muladd_fp64 = res_muladd_fp64 * fp64 + fp64;
		res_muladd_fp32 = res_muladd_fp32 * fp32 + fp32;
	}

	double err_add = fabs(res_add_fp64 - (double)res_add_fp32);
	double err_mul = fabs(res_mul_fp64 - (double)res_mul_fp32);
	double err_muladd = fabs(res_muladd_fp64 - (double)res_muladd_fp32);

	printf("FP64 Reference Add: %.17f\n", res_add_fp64);
	printf("CPU FP32 Test Add:  %.17f\n", (double)res_add_fp32);
	printf("Absolute Error Add: %e\n\n", err_add);

	printf("FP64 Reference Mul: %.17f\n", res_mul_fp64);
	printf("CPU FP32 Test Mul:  %.17f\n", (double)res_mul_fp32);
	printf("Absolute Error Mul: %e\n\n", err_mul);

	printf("FP64 Reference Mul&Add: %.17f\n", res_muladd_fp64);
	printf("CPU FP32 Test Mul&Add:  %.17f\n", (double)res_muladd_fp32);
	printf("Absolute Error Mul&Add: %e\n\n", err_muladd);
}

#ifndef _CUDA_NVCC_COMPAT_COMPILER
int main(void)
{
	base();
	precision_error();
	return 0;
}
#endif
