// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
/******************************************************************************\
 *             PTI - CUDA Profiling Tools Interface                           *
\******************************************************************************/
#ifndef __CUDA_ADAPTER_PTI_VERSION_H
#define __CUDA_ADAPTER_PTI_VERSION_H 1

#ifdef _CUPTI_VERSION_H_
#error "CudaAdapter not allow include origin CUDA cupti_version.h"
#endif

#include "wrapper_defs.h"

#define CUPTI_API_VERSION CUX(PTI_API_VERSION)
/**
 * CUptiResult cuptiGetVersion(uint32_t *version);
 */
#define cuptiGetVersion cuX(ptiGetVersion)

#ifdef __USE_HPCC__
#elif defined(__USE_LUCA__)
#elif defined(__USE_HIP__)
#endif

#endif
