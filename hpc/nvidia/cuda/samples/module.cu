// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include "hpcc_helpers.h"
#include "cuda2hccl.h"
#else
#include <cuda.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#endif

#define MODULE_CUBIN	".output/hello.cubin"
#define MODULE_FUNC	"dev_foo"

int main(void)
{
	CUmodule mod;
	CUfunction func;

	cuModuleLoad(&mod, MODULE_CUBIN);
	cuModuleGetFunction(&func, mod, MODULE_FUNC);

	return 0;
}
