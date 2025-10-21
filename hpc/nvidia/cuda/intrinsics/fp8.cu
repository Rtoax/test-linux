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

#if !defined(__HPCC__) && !defined(__LUCA__) && !defined(__HIPCC__) && defined(__CUDACC__) && CUDA_VERSION >= 13000
# define SUPPORT_FP8_E8M0	1
#endif

__global__ void k_fp8_functions(void)
{
	const __nv_bfloat16_raw __unused bf16_one_raw = { .x = USHORT_ONE_BF16, };
	const __nv_bfloat162_raw __unused bf162_1_raw = { .x = 1, .y = 1, };
	const __nv_bfloat162_raw __unused bf162_one_raw = { .x = USHORT_ONE_BF16, .y = USHORT_ONE_BF16, };
	const double2 d2_pi = make_double2(PI_DOUBLE, PI_DOUBLE);
	const float2 f2_pi = make_float2(PI_FLOAT, PI_FLOAT);

	__half_raw halfraw;
	__half_raw halfraw_one = { .x = USHORT_ONE_FP16, };
	__half2_raw half2raw;

	__nv_fp8_storage_t __unused fp8_1;
	__nv_fp8x2_storage_t __unused fp8x2_1;

	PBF16RAW(bf16_one_raw);
	PBF162RAW(bf162_1_raw);
	PBF162RAW(bf162_one_raw);

	PHALFRAW(halfraw_one);
	PFP8E4M3((fp8_1 = __nv_cvt_halfraw_to_fp8(halfraw_one, __NV_NOSAT, __NV_E4M3)));

	/**
	 * HPCC 3.0.0 BUG: Why print fp8_1 <__NV_E4M3> : inf??
	 * commit f44b19db66fb ("fp8.cu: Report HPCC 3.0.0 BUG")
	 */
	PFP8E4M3((fp8_1 = __nv_cvt_double_to_fp8(PI_DOUBLE, __NV_NOSAT, __NV_E4M3)));
	PBITS(&fp8_1, 8);

	PHALFRAW((halfraw = __nv_cvt_fp8_to_halfraw(fp8_1, __NV_E4M3)));
	PBITS(&halfraw, 16);

	PFP8E4M3((fp8_1 = __nv_cvt_float_to_fp8(PI_FLOAT, __NV_NOSAT, __NV_E4M3)));

	PFP8E4M3((fp8_1 = __nv_cvt_bfloat16raw_to_fp8(bf16_one_raw, __NV_NOSAT, __NV_E4M3)));
	PFP8x2E4M3((fp8x2_1 = __nv_cvt_bfloat16raw2_to_fp8x2(bf162_1_raw, __NV_NOSAT, __NV_E4M3)));
	PFP8x2E4M3((fp8x2_1 = __nv_cvt_bfloat16raw2_to_fp8x2(bf162_one_raw, __NV_NOSAT, __NV_E4M3)));
	PFP8x2E4M3((fp8x2_1 = __nv_cvt_double2_to_fp8x2(d2_pi, __NV_NOSAT, __NV_E4M3)));
	PFP8x2E4M3((fp8x2_1 = __nv_cvt_float2_to_fp8x2(f2_pi, __NV_NOSAT, __NV_E4M3)));

	PHALF2RAW((half2raw = __nv_cvt_fp8x2_to_halfraw2(fp8x2_1, __NV_E4M3)));
	PFP8x2E4M3((__nv_cvt_halfraw2_to_fp8x2(half2raw, __NV_NOSAT, __NV_E4M3)));

#ifdef SUPPORT_FP8_E8M0
	PFP8E8M0((fp8_1 = __nv_cvt_bfloat16raw_to_e8m0(bf16_one_raw, __NV_NOSAT, cudaRoundZero)));
	PBF16RAW(__nv_cvt_e8m0_to_bf16raw(fp8_1));

	PFP8E8M0((fp8_1 = __nv_cvt_float_to_e8m0(PI_FLOAT, __NV_NOSAT, cudaRoundZero)));

	PFP8x2E8M0((fp8x2_1 = __nv_cvt_double2_to_e8m0x2(d2_pi, __NV_NOSAT, cudaRoundZero)));
	PBF162RAW(__nv_cvt_e8m0x2_to_bf162raw(fp8x2_1));

	PFP8x2E8M0((fp8x2_1 = __nv_cvt_float2_to_e8m0x2(f2_pi, __NV_NOSAT, cudaRoundZero)));

	PFP8x2E8M0((fp8x2_1 = __nv_cvt_bfloat162raw_to_e8m0x2(bf162_1_raw, __NV_NOSAT, cudaRoundZero)));
	PFP8x2E8M0((fp8x2_1 = __nv_cvt_bfloat162raw_to_e8m0x2(bf162_one_raw, __NV_NOSAT, cudaRoundZero)));
	PBF162RAW(__nv_cvt_e8m0x2_to_bf162raw(fp8x2_1));

	PFP8E8M0((fp8_1 = __nv_cvt_float_to_e8m0(999, __NV_NOSAT, cudaRoundZero)));
	PFP8E8M0((fp8_1 = __nv_cvt_double_to_e8m0(999, __NV_NOSAT, cudaRoundZero)));
#endif
}

int main(int argc, char *argv[])
{
	assert(sizeof(__nv_fp8_e4m3) == 1 && "bad size of __nv_fp8_e4m3");
	assert(sizeof(__nv_fp8_e5m2) == 1 && "bad size of __nv_fp8_e5m2");
	assert(sizeof(__nv_fp8x2_storage_t) == 2 && "bad size of __nv_fp8x2_storage_t");
	assert(sizeof(__nv_fp8x4_storage_t) == 4 && "bad size of __nv_fp8x4_storage_t");
	assert(sizeof(__nv_fp8x2_e4m3) == 2 && "bad size of __nv_fp8x2_e4m3");
	assert(sizeof(__nv_fp8x4_e4m3) == 4 && "bad size of __nv_fp8x4_e4m3");
	assert(sizeof(__nv_fp8x2_e5m2) == 2 && "bad size of __nv_fp8x2_e5m2");
	assert(sizeof(__nv_fp8x4_e5m2) == 4 && "bad size of __nv_fp8x4_e5m2");
#ifdef SUPPORT_FP8_E8M0
	assert(sizeof(__nv_fp8x2_e8m0) == 2 && "bad size of __nv_fp8x2_e8m0");
	assert(sizeof(__nv_fp8x4_e8m0) == 4 && "bad size of __nv_fp8x4_e8m0");
#endif

	k_fp8_functions<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
