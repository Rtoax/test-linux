// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "cuda.hpp"


CUresult cuModuleLoad(CUmodule* module, const char *fname)
{
	return CUDA_SUCCESS;
}

CUresult cuModuleUnload(CUmodule module)
{
	return CUDA_SUCCESS;
}

CUresult cuModuleGetFunction(CUfunction* hfunc, CUmodule hmod, const char *name)
{
	return CUDA_SUCCESS;
}

CUresult cuModuleLoadData(CUmodule *module, const void *image)
{
	return CUDA_SUCCESS;
}

CUresult cuModuleLoadDataEx(CUmodule *module, const void *image,
			    unsigned int numOptions, CUjit_option *options,
			    void **optionValues)
{
	return CUDA_SUCCESS;
}
