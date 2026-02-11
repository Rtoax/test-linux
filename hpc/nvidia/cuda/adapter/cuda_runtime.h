// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_CUDA_RUNTIME_H
#define __CUDA_ADAPTER_CUDA_RUNTIME_H 1

#include "wrapper_defs.h"
#include "cuda_runtime_api.h"

/**
 * CUDA: typedef struct CUstream_st *CUstream;
 * LUCA: typedef struct LCstream_st *lcStream_t;
 */
#define cudaStream_t __cuda(Stream_t)

#endif
