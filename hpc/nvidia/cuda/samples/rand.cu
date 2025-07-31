// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#if defined(HAVE_HCCL)
# include <hc_runtime.h>
# include <hcrand/hcrand.h>
# include "hpcc_helpers.h"
# include "cuda2hccl.h"
# define NAME	"MetaX RAND"
#elif defined(HAVE_CUDA)
# include <cuda_runtime.h>
# include <curand.h>
# include "cuda_helpers.h"
# define NAME	"CUDA RAND"
#else
# error "Must define one of HAVE_HCCL, HAVE_CUDA"
#endif


int main(int argc, char *argv[])
{
	int version;
	curandGetVersion(&version);
	printf(NAME " version %d\n", version);
	return 0;
}
