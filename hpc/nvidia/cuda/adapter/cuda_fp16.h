// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
#ifndef __CUDA_ADAPTER_FP16_H
#define __CUDA_ADAPTER_FP16_H 1

#ifdef __CUDA_FP16_H__
#error "CudaAdapter not allow include origin CUDA cuda_fp16.h"
#endif

#include "wrapper_defs.h"

#ifdef __USE_HPCC__
# include <hpcc_fp16.h>
#elif defined(__USE_LUCA__)
# include <luca_fp16.h>
#elif defined(__USE_HIP__)
# define HIPBLAS_USE_HIP_HALF
# include <hip/hip_fp16.h>
#endif

#endif
