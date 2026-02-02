// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
#ifndef __CUDA_ADAPTER_FP6_H
#define __CUDA_ADAPTER_FP6_H 1

/**
 * fp6
 *   typedef __nv_fp8_storage_t __nv_fp6_storage_t;
 *   typedef __nv_fp8x2_storage_t __nv_fp6x2_storage_t;
 *   typedef __nv_fp8x4_storage_t __nv_fp6x4_storage_t;
 */
#define __nv_fp6_storage_t ____nv_(fp6_storage_t)
#define __nv_fp6x2_storage_t ____nv_(fp6x2_storage_t)
#define __nv_fp6x4_storage_t ____nv_(fp6x4_storage_t)

#define __nv_fp6_e2m3 ____nv_(fp6_e2m3)
#define __nv_fp6_e3m2 ____nv_(fp6_e3m2)
#define __nv_fp6x2_e2m3 ____nv_(fp6x2_e2m3)
#define __nv_fp6x2_e3m2 ____nv_(fp6x2_e3m2)
#define __nv_fp6x4_e2m3 ____nv_(fp6x4_e2m3)
#define __nv_fp6x4_e3m2 ____nv_(fp6x4_e3m2)

#define __nv_fp6_interpretation_t ____nv_(fp6_interpretation_t)
#define __NV_E2M3 ____NV_(E2M3)
#define __NV_E3M2 ____NV_(E3M2)

#endif
