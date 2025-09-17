// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#pragma once

#ifdef HAVE_HPCC
#define CUresult	hcError_t
typedef enum hcLimit_t hcLimit_t;
typedef enum cudaDeviceAttr cudaDeviceAttr;
typedef struct hcMemLocation hcMemLocation;
typedef void *cudaKernel_t;
#else /* fallback to CUDA */
typedef struct cudaDeviceProp cudaDeviceProp;
typedef enum cudaDeviceAttr cudaDeviceAttr;
typedef enum cudaMemcpyKind cudaMemcpyKind;
typedef enum cudaMemoryAdvise cudaMemoryAdvise;
typedef struct cudaMemLocation cudaMemLocation;
typedef enum cudaLimit cudaLimit;
#endif

#ifndef __cplusplus
/* TODO: _Float32 may not supported */
typedef _Float32 __half;
#endif
