// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * Refs:
 * - https://github.com/ROCm/rocm-systems.git
 */
#pragma once
#include <sys/types.h>

#ifndef __USE_HIP__
# error "This header only used by HIP code"
#endif

#ifdef __cplusplus
extern "C" {
#endif

int hipGetStreamDeviceId(hipStream_t stream);

hipError_t hipMemcpyWithStream(void* dst, const void* src, size_t sizeBytes,
                               hipMemcpyKind kind, hipStream_t stream);

hiprtcResult hiprtcGetCode(hiprtcProgram prog, char* code);

#ifdef __cplusplus
}
#endif
