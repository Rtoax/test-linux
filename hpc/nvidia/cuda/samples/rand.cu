// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#if defined(HAVE_HPCC)
# include <hc_runtime.h>
# include <hcrand/hcrand.h>
# include "cuda_adapter.h"
# define NAME	"MetaX RAND"
#elif defined(HAVE_HIP)
#include <hip/hip_runtime.h>
#include <hiprand/hiprand.h>
#include "cuda_adapter.h"
# define NAME	"AMDGPU RAND"
#else
# include <cuda_runtime.h>
# include <curand.h>
# define NAME	"CUDA RAND"
#endif
#include "cuda_helpers.h"


int main(int argc, char *argv[])
{
	int version;
	CURAND_CHECK(curandGetVersion(&version), exit(1));
	printf(NAME " version %d\n", version);
	return 0;
}
