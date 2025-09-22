// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#if defined(HAVE_HCCL)
# include <hc_runtime.h>
# include <hcfft/hcfft.h>
# include "hpcc_helpers.h"
# include "cuda_adapter.h"
# define NAME	"MetaX FFT"
#elif defined(HAVE_HIP)
#include <hip/hip_runtime.h>
#include <hipfft/hipfft.h>
#include "cuda_helpers.h"
#include "cuda_adapter.h"
# define NAME	"AMDGPU FFT"
#else
# include <cuda_runtime.h>
# include <cufft.h>
# include "cuda_helpers.h"
# define NAME	"CUDA FFT"
#endif


int main(int argc, char *argv[])
{
	int major, minor, patch;
	cufft_version(&major, &minor, &patch);

	printf("cuFFT version %d.%d.%d\n", major, minor, patch);

	return 0;
}
