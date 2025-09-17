// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#pragma once

typedef struct cudaDeviceProp cudaDeviceProp;
typedef enum cudaDeviceAttr cudaDeviceAttr;
typedef enum cudaMemcpyKind cudaMemcpyKind;
typedef enum cudaMemoryAdvise cudaMemoryAdvise;
typedef struct cudaMemLocation cudaMemLocation;

#ifndef __cplusplus
/* TODO: _Float32 may not supported */
typedef _Float32 __half;
#endif
