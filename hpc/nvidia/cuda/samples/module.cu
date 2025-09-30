// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include "cuda_compat.h"
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
