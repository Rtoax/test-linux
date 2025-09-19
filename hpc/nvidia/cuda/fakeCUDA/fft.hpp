// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#ifdef HAVE_HPCC
#include <hc_runtime.h>
#include <hcfft/hcfft.h>
#include <cuda_adapter.h>
#else
#include <cufft.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

cufftResult cufftGetProperty(libraryPropertyType type, int *value);

#ifdef __cplusplus
}
#endif
