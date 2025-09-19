// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "cuda.hpp"


CUresult cuModuleLoad(CUmodule* module, const char *fname)
{
	return CUDA_SUCCESS;
}

CUresult cuModuleGetFunction(CUfunction* hfunc, CUmodule hmod, const char *name)
{
	return CUDA_SUCCESS;
}
