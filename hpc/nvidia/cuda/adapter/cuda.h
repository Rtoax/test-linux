// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_CUDA_H
#define __CUDA_ADAPTER_CUDA_H 1

/**
 * CUDA: typedef __device_builtin__ struct CUstream_st *cudaStream_t;
 */
#define CUstream_st __CU(stream_st)

#endif
