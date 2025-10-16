// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INTRINSIC__FP8.html
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


__global__ void k_fp8_functions(void)
{
	const __nv_bfloat16_raw __unused bf16_1_raw = { .x = 1, };
	const __nv_bfloat16_raw __unused bf16_2_raw = { .x = 2, };
	const __nv_bfloat162_raw __unused bf162_1_raw = { .x = 1, .y = 1, };
	const __nv_bfloat162_raw __unused bf162_2_raw = { .x = 2, .y = 2, };

	__half_raw halfraw;
	__half2_raw half2raw;

	__nv_fp8_storage_t __unused fp8_1;
	__nv_fp8x2_storage_t __unused fp8x2_1;

	PBF162RAW(bf162_1_raw);
	PBF162RAW(bf162_2_raw);

	/**
	 * FIXME: Why print fp8_1 <__NV_E4M3> : inf??
	 */
	PEXPR(fp8_1 = __nv_cvt_double_to_fp8(PI_DOUBLE, __NV_NOSAT, __NV_E4M3));
	PFP8(fp8_1, __NV_E4M3);
	PBITS(&fp8_1, 8);

	halfraw = __nv_cvt_fp8_to_halfraw(fp8_1, __NV_E4M3);
	PBITS(&halfraw, 16);
	PHALFRAW(halfraw);

	fp8_1 = __nv_cvt_bfloat16raw_to_fp8(bf16_1_raw, __NV_NOSAT, __NV_E4M3);
	fp8x2_1 = __nv_cvt_bfloat16raw2_to_fp8x2(bf162_1_raw, __NV_NOSAT, __NV_E4M3);
#if !defined(__HPCC__) && !defined(__HIPCC__) && CUDA_VERSION >= 13000
	fp8_1 = __nv_cvt_bfloat16raw_to_e8m0(bf16_1_raw, __NV_NOSAT, cudaRoundZero);
	fp8x2_1 = __nv_cvt_bfloat162raw_to_e8m0x2(bf162_1_raw, __NV_NOSAT, cudaRoundZero);
#endif
}

int main(int argc, char *argv[])
{
	assert(sizeof(__nv_fp8_e4m3) == 1 && "bad size of __nv_fp8_e4m3");
	assert(sizeof(__nv_fp8_e5m2) == 1 && "bad size of __nv_fp8_e5m2");
	assert(sizeof(__nv_fp8x2_e4m3) == 2 && "bad size of __nv_fp8x2_e4m3");
	assert(sizeof(__nv_fp8x4_e4m3) == 4 && "bad size of __nv_fp8x4_e4m3");
	assert(sizeof(__nv_fp8x2_e5m2) == 2 && "bad size of __nv_fp8x2_e5m2");
	assert(sizeof(__nv_fp8x4_e5m2) == 4 && "bad size of __nv_fp8x4_e5m2");
#if !defined(__HPCC__) && !defined(__HIPCC__) && CUDA_VERSION >= 13000
	assert(sizeof(__nv_fp8x2_e8m0) == 4 && "bad size of __nv_fp8x2_e8m0");
	assert(sizeof(__nv_fp8x4_e8m0) == 4 && "bad size of __nv_fp8x4_e8m0");
#endif

	k_fp8_functions<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
