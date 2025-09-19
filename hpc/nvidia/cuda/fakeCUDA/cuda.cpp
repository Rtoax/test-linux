// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "device.h"
#include "cuda.hpp"


CUresult cuDeviceGet(CUdevice *device, int ordinal)
{
	if (ordinal < 0 || ordinal >= dev_count())
		return CUDA_ERROR_INVALID_VALUE;
	/**
	 * Note: CUdevice/CUdevice_v1 is type of 'int'
	 * https://docs.nvidia.com/cuda/cuda-driver-api/group__CUDA__TYPES.html
	 */
	*device = ordinal;

	return CUDA_SUCCESS;
}

CUresult cuDeviceComputeCapability(int *major, int *minor, CUdevice dev)
{
	if (dev < 0 || dev >= dev_count())
		return CUDA_ERROR_INVALID_VALUE;

	*major = dev_major(dev);
	*minor = dev_minor(dev);

	return CUDA_SUCCESS;
}
