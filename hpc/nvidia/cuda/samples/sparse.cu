// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#if defined(HAVE_HPCC)
# include <hc_runtime.h>
# include "cuda_adapter.h"
# define NAME	"MetaX SPARSE"
#elif defined(HAVE_HIP)
#include <hip/hip_runtime.h>
#include <hipsparse/hipsparse.h>
#include "cuda_adapter.h"
# define NAME	"AMDGPU SPARSE"
#else
# include <cuda_runtime.h>
# define NAME	"CUDA SPARSE"
#endif
#include "cuda_helpers.h"


int main(int argc, char *argv[])
{
	int major, minor, patch;

	cusparse_version(&major, &minor, &patch);
	printf("cuSPARSE version %d.%d.%d\n", major, minor, patch);

	return 0;
}
