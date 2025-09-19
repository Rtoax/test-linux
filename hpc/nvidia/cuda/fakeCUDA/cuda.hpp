// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "device.h"
#include "compat.hpp"


#ifdef __cplusplus
extern "C" {
#endif

#if defined(__USE_HPCC__)
# define CUresult	hcError_t
# undef CUDA_ERROR_INVALID_VALUE
# define CUDA_ERROR_INVALID_VALUE	cudaErrorInvalidValue
# undef CUDA_SUCCESS
# define CUDA_SUCCESS	cudaSuccess
#endif

CUresult cuDeviceGet(CUdevice *device, int ordinal);

CUresult cuDeviceComputeCapability(int *major, int *minor, CUdevice dev);

CUresult cuModuleLoad(CUmodule* module, const char *fname);

CUresult cuModuleGetFunction(CUfunction* hfunc, CUmodule hmod, const char *name);

#ifdef __cplusplus
}
#endif
