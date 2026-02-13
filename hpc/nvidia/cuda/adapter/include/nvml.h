// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
/******************************************************************************\
 *             NVML: NVIDIA Management Library                                *
\******************************************************************************/
#ifndef __CUDA_ADAPTER_NCCL_H
#define __CUDA_ADAPTER_NCCL_H 1

#ifdef __nvml_nvml_h__
#error "CudaAdapter not allow include origin CUDA nvml.h"
#endif

#include "wrapper_defs.h"

#ifdef __USE_HPCC__
#elif defined(__USE_LUCA__)
#elif defined(__USE_HIP__)
#endif

#endif
