// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <cuda.h>
#if !defined(__HPCC__) && !defined(__LUCA__) && !defined(__HIPCC__) && \
	CUDA_VERSION > 12040
# define __have_fp4
#else
# warning "Not support FP4"
#endif
#include <assert.h>
#include <stdio.h>
#include <cuda_runtime.h>
#if defined(__have_fp4)
#include <cuda_fp4.h>
#endif
#include "compiler.h"
#include "print.h"
#include "types.h"

#if defined(__have_fp4)
__global__ void k_fp4_types(void)
{
	__nv_fp4_storage_t __unused fp4_s;
	__nv_fp4x2_storage_t __unused fp4x2_s;
	__nv_fp4x4_storage_t __unused fp4x4_s;

	__nv_fp4_e2m1 __unused fp4_e2m1;
	__nv_fp4x2_e2m1 __unused fp4x2_e2m1;
	__nv_fp4x4_e2m1 __unused fp4x4_e2m1;
}

__global__ void k_fp4_convert(void)
{
	double2 d2_pi = make_double2(PI_DOUBLE, PI_DOUBLE);
	float2 f2_pi = make_float2(PI_FLOAT, PI_FLOAT);
	__half_raw hraw_one = {
		.x = USHORT_ONE_FP16,
	};
	__half2_raw h2raw_one = {
		.x = USHORT_ONE_FP16,
		.y = USHORT_ONE_FP16,
	};
	__nv_bfloat16_raw bf16_one_raw = {
		.x = USHORT_ONE_BF16,
	};
	__nv_bfloat162_raw bf162_one_raw = {
		.x = 1,
		.y = 1,
	};

	PDOUBLE2(d2_pi);
	PFLOAT2(f2_pi);
	PHALF2RAW(h2raw_one);
	PBF16RAW(bf16_one_raw);
	PBF162RAW(bf162_one_raw);

	PFP4E2M1(
		__nv_cvt_double_to_fp4(PI_DOUBLE, __NV_E2M1, cudaRoundNearest));
	/* TODO: wrong! */
	PFP4x2E2M1(
		__nv_cvt_double2_to_fp4x2(d2_pi, __NV_E2M1, cudaRoundNearest));

	PFP4E2M1(__nv_cvt_float_to_fp4(PI_FLOAT, __NV_E2M1, cudaRoundNearest));
	/* TODO: wrong! */
	PFP4x2E2M1(
		__nv_cvt_float2_to_fp4x2(f2_pi, __NV_E2M1, cudaRoundNearest));

	PFP4E2M1(
		__nv_cvt_halfraw_to_fp4(hraw_one, __NV_E2M1, cudaRoundNearest));
	/* TODO: wrong! */
	PFP4x2E2M1(__nv_cvt_halfraw2_to_fp4x2(h2raw_one, __NV_E2M1,
					      cudaRoundNearest));

	PFP4E2M1(__nv_cvt_bfloat16raw_to_fp4(bf16_one_raw, __NV_E2M1,
					     cudaRoundNearest));
	/* TODO: wrong! */
	PFP4x2E2M1(__nv_cvt_bfloat16raw2_to_fp4x2(bf162_one_raw, __NV_E2M1,
						  cudaRoundNearest));
}
#endif

int main(int argc, char *argv[])
{
#if defined(__have_fp4)
	assert(sizeof(__nv_fp4_storage_t) == 1 &&
	       "bad size of __nv_fp4_storage_t");
	assert(sizeof(__nv_fp4x2_storage_t) == 1 &&
	       "bad size of __nv_fp4x2_storage_t");
	assert(sizeof(__nv_fp4x4_storage_t) == 2 &&
	       "bad size of __nv_fp4x4_storage_t");

	assert(sizeof(__nv_fp4_e2m1) == 1 && "bad size of __nv_fp4_e2m1");
	assert(sizeof(__nv_fp4x2_e2m1) == 1 && "bad size of __nv_fp4x2_e2m1");
	assert(sizeof(__nv_fp4x4_e2m1) == 2 && "bad size of __nv_fp4x4_e2m1");

	k_fp4_types<<<1, 1>>>();
	k_fp4_convert<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
#endif
	return 0;
}
