// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#ifdef HAVE_HPCC
#include <hc_runtime.h>
#include <hcc/hcc_internal.h>
#include <cuda_adapter.h>
#else
#include <cuda.h>
#include <cuda_runtime.h>
#endif
#include "types.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAVE_HPCC
# define CUresult	hcError_t
# undef CUDA_ERROR_INVALID_VALUE
# define CUDA_ERROR_INVALID_VALUE	cudaErrorInvalidValue
# undef CUDA_SUCCESS
# define CUDA_SUCCESS	cudaSuccess
#endif

CUresult cuModuleLoad(CUmodule* module, const char *fname)
{
	return CUDA_SUCCESS;
}

CUresult cuModuleGetFunction(CUfunction* hfunc, CUmodule hmod, const char *name)
{
	return CUDA_SUCCESS;
}
#ifdef __cplusplus
}
#endif
