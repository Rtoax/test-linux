// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "device.h"
#include "compat.hpp"


#ifdef __cplusplus
extern "C" {
#endif

#if defined(__USE_HPCC__)
# undef CUresult
# undef CUdevice
# undef CUmodule
# undef CUfunction
# undef CUDA_ERROR_INVALID_VALUE
# undef CUDA_SUCCESS

# define CUresult	hcError_t
# define CUdevice	hcDevice_t
# define CUmodule	hcModule_t
# define CUfunction	hcFunction_t
# define CUDA_ERROR_INVALID_VALUE	cudaErrorInvalidValue
# define CUDA_SUCCESS	cudaSuccess
#elif defined(__USE_HIP__)
# undef CUresult
# undef CUdevice
# undef CUmodule
# undef CUfunction
# undef CUDA_ERROR_INVALID_VALUE
# undef CUDA_SUCCESS

# define CUresult	hipError_t
# define CUdevice	hipDevice_t
# define CUmodule	hipModule_t
# define CUfunction	hipFunction_t
# define CUDA_ERROR_INVALID_VALUE	hipErrorInvalidValue
# define CUDA_SUCCESS	hipSuccess
#endif

CUresult cuDeviceGet(CUdevice *device, int ordinal);

CUresult cuDeviceComputeCapability(int *major, int *minor, CUdevice dev);

CUresult cuModuleLoad(CUmodule* module, const char *fname);
CUresult cuModuleUnload(CUmodule module);

CUresult cuModuleGetFunction(CUfunction* hfunc, CUmodule hmod, const char *name);

#ifdef __cplusplus
}
#endif
