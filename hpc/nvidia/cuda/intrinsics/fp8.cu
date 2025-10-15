// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
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


int main(int argc, char *argv[])
{
	assert(sizeof(__nv_fp8_e4m3) == 1 && "bad size of __nv_fp8_e4m3");
	assert(sizeof(__nv_fp8_e5m2) == 1 && "bad size of __nv_fp8_e5m2");
	assert(sizeof(__nv_fp8x2_e4m3) == 2 && "bad size of __nv_fp8x2_e4m3");
	assert(sizeof(__nv_fp8x4_e4m3) == 4 && "bad size of __nv_fp8x4_e4m3");
	assert(sizeof(__nv_fp8x2_e5m2) == 2 && "bad size of __nv_fp8x2_e5m2");
	assert(sizeof(__nv_fp8x4_e5m2) == 4 && "bad size of __nv_fp8x4_e5m2");
#if !defined(__HPCC__) && !defined(__HIPCC__)
	assert(sizeof(__nv_fp8x2_e8m0) == 4 && "bad size of __nv_fp8x2_e8m0");
	assert(sizeof(__nv_fp8x4_e8m0) == 4 && "bad size of __nv_fp8x4_e8m0");
#endif

	(void)cudaDeviceSynchronize();
	return 0;
}
