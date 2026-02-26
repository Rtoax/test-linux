// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
#ifndef __CUDA_ADAPTER_BF16_H
#define __CUDA_ADAPTER_BF16_H 1

#ifdef __CUDA_BF16_H__
#error "CudaAdapter not allow include origin CUDA cuda_bf16.h"
#endif

#include "wrapper_defs.h"

/**
 * bfloat16
 *
 *   typedef struct __CUDA_ALIGN__(2) {
 *     unsigned short x;
 *   } __nv_bfloat16_raw;
 *
 *   typedef struct __CUDA_ALIGN__(4) {
 *     unsigned short x;
 *     unsigned short y;
 *   } __nv_bfloat162_raw;
 */
#define __nv_bfloat16 __nv_X(bfloat16)
#define __nv_bfloat16_raw __nv_X(bfloat16_raw)
#define __nv_bfloat162 __nv_X(bfloat162)
#define __nv_bfloat162_raw __nv_X(bfloat162_raw)

#define __nv_cvt_bfloat16raw_to_e8m0 __nv_X(cvt_bfloat16raw_to_e8m0)
#define __nv_cvt_bfloat16raw_to_fp8 __nv_X(cvt_bfloat16raw_to_fp8)

#define __nv_cvt_bfloat162raw_to_e8m0x2 __nv_X(cvt_bfloat162raw_to_e8m0x2)
#define __nv_cvt_bfloat16raw2_to_fp8x2 __nv_X(cvt_bfloat16raw2_to_fp8x2)

#define __nv_cvt_e8m0_to_bf16raw __nv_X(cvt_e8m0_to_bf16raw)
#define __nv_cvt_e8m0x2_to_bf162raw __nv_X(cvt_e8m0x2_to_bf162raw)

#ifdef __USE_HPCC__
# include <hpcc_fp8.h>
#elif defined(__USE_LUCA__)
# include <luca_fp8.h>
#elif defined(__USE_HIP__)
# include <hip/hip_fp8.h>
#endif

#endif
