// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INT.html
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INTRINSIC__INT.html
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
	short2 s;
	s.x = 1;
	s.y = 2;
}

__global__ void k_integer_mathematical(void)
{
	int i = 1;
	long int li = 1L;
	long long int lli_a = 1LL, lli_b = 2LL;

	PUINT32(i);
	PLONG(li);
	PLONGLONG(lli_a);
	PLONGLONG(lli_b);

	PUINT32(abs(-1));
	PLONG(abs(-1L));
	PLONGLONG(abs(-1LL));
	PLONG(labs(-1L));
	PLONGLONG(llabs(-1LL));
#if !defined(__HIPCC__)
	PLONGLONG(llmax(1LL, 2LL));
	PLONGLONG(llmin(1LL, 2LL));
#endif
	PLONG(max(1L, 2L));
	PLONGLONG(max(1LL, 2LL));
	PLONG(max(1ULL, 2ULL));
}

int main(int argc, char *argv[])
{
	assert(sizeof(int) == 4 && "bad size of int");
	assert(sizeof(short2) == 4 && "bad size of short2");

	k_integer_types<<<1, 1>>>();
	k_integer_mathematical<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
