// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#pragma once
#include "device.h"
#include "compat.hpp"


#ifdef __cplusplus
extern "C" {
#endif

CUresult cuDeviceGet(CUdevice *device, int ordinal);

CUresult cuDeviceComputeCapability(int *major, int *minor, CUdevice dev);

CUresult cuModuleLoad(CUmodule* module, const char *fname);
CUresult cuModuleUnload(CUmodule module);

CUresult cuModuleGetFunction(CUfunction* hfunc, CUmodule hmod, const char *name);

CUresult cuModuleLoadData(CUmodule *module, const void *image);
CUresult cuModuleLoadDataEx(CUmodule *module, const void *image,
			    unsigned int numOptions, CUjit_option *options,
			    void **optionValues);

#ifdef __cplusplus
}
#endif
