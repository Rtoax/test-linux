// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INT.html
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
#include "types.h"


__global__ void k_integer_types(void)
{
}

__global__ void k_integer_mathematical(void)
{
	int i = 1;
	long int li = 1L;
	long long int lli_a = 1LL, lli_b = 2LL;

	PINT(i);
	PLONG(li);
	PLONGLONG(lli_a);
	PLONGLONG(lli_b);

	PINT(abs(-1));
	PLONG(abs(-1L));
	PLONGLONG(abs(-1LL));
	PLONG(labs(-1L));
	PLONGLONG(llabs(-1LL));
	PLONGLONG(llmax(1LL, 2LL));
	PLONGLONG(llmin(1LL, 2LL));
	PLONG(max(1L, 2L));
	PLONGLONG(max(1LL, 2LL));
	PLONG(max(1ULL, 2ULL));
}

int main(int argc, char *argv[])
{
	assert(sizeof(int) == 4 && "bad size of int");

	k_integer_types<<<1, 1>>>();
	k_integer_mathematical<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
