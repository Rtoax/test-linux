// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#if defined(HAVE_HPCC)
# define __USE_HPCC__	1
#include <hc_runtime.h>
#include "cuda_adapter.h"
#elif defined(HAVE_HIP)
# define __USE_HIP__	1
#include <hip/hip_runtime.h>
#include "cuda_adapter.h"
#else
#include <cuda.h>
#include <cuda_runtime.h>
#endif
#include "cuda_helpers.h"

#if defined(HAVE_HPCC)
#define MODULE_CUBIN	".output/hello.devbin"
#elif defined(HAVE_HIP)
#define MODULE_CUBIN	".output/parallel.hip_fatbin"
#else
#define MODULE_CUBIN	".output/hello.cubin"
#endif
#define MODULE_FUNC	"kern_func"

int main(void)
{
	CUmodule mod;
	CUfunction func;

	cuModuleLoad(&mod, MODULE_CUBIN);
	cuModuleGetFunction(&func, mod, MODULE_FUNC);

	return 0;
}
