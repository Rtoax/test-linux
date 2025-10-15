// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__DOUBLE.html
 */
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "cuda_compat.h"
#include "compiler.h"
#include "print.h"


__global__ void k_double_precision_mathematical(void)
{
	double pi = 3.141592653;

	PDOUBLE(pi);

	PDOUBLE(acos(pi))
	PDOUBLE(acosh(pi))
	PDOUBLE(asin(pi))
	PDOUBLE(asinh(pi))
	PDOUBLE(atan(pi))
	PDOUBLE(atan2(pi, pi))
	PDOUBLE(atanh(pi))

	PDOUBLE(cbrt(pi))
	PDOUBLE(ceil(pi))
	PDOUBLE(copysign(pi, pi))
	PDOUBLE(cos(pi))
	PDOUBLE(cosh(pi))
	PDOUBLE(cospi(pi))
}

int main(int argc, char *argv[])
{
	assert(sizeof(double) == 8 && "bad size of double");

	k_double_precision_mathematical<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
