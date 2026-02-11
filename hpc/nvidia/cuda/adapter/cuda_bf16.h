// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
#ifndef __CUDA_ADAPTER_BF16_H
#define __CUDA_ADAPTER_BF16_H 1

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
#define __nv_bfloat16 ____nv_(bfloat16)
#define __nv_bfloat16_raw ____nv_(bfloat16_raw)
#define __nv_bfloat162 ____nv_(bfloat162)
#define __nv_bfloat162_raw ____nv_(bfloat162_raw)

#define __nv_cvt_bfloat16raw_to_e8m0 ____nv_(cvt_bfloat16raw_to_e8m0)
#define __nv_cvt_bfloat16raw_to_fp8 ____nv_(cvt_bfloat16raw_to_fp8)

#define __nv_cvt_bfloat162raw_to_e8m0x2 ____nv_(cvt_bfloat162raw_to_e8m0x2)
#define __nv_cvt_bfloat16raw2_to_fp8x2 ____nv_(cvt_bfloat16raw2_to_fp8x2)

#define __nv_cvt_e8m0_to_bf16raw ____nv_(cvt_e8m0_to_bf16raw)
#define __nv_cvt_e8m0x2_to_bf162raw ____nv_(cvt_e8m0x2_to_bf162raw)

#endif
