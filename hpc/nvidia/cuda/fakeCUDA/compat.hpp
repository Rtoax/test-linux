// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#ifndef __FAKECUDA_COMPAT
#define __FAKECUDA_COMPAT 1

#ifdef __USE_HPCC__
#include <hcr/hc_runtime.h>
#include <hcr/hcrtc.h>
#include <hcc/hcc_internal.h>
#include <hcblas/hcblas.h>
#include <hcblas/hcblasLt.h>
#include <hcsparse/hcsparse.h>
#include <hcrand/hcrand.h>
#include <hcfft/hcfft.h>
/* TODO: add rtc */
#include <hpcc_fp16.h>
#include <cuda_adapter.h>
# ifndef HAVE_HPCC
#  error "Not found HPCC envrioment, but use HPCC"
# endif
#elif defined(__USE_HIP__)
/**
 * Must define exactly one of __HIP_PLATFORM_AMD__ or __HIP_PLATFORM_NVIDIA__
 */
# define __HIP_PLATFORM_AMD__
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>
#include <hip/hiprtc.h>
#include <hipfft/hipfft.h>
#include <hipsparse/hipsparse.h>
#include <hiprand/hiprand.h>
#include <hipblas/hipblas.h>
#include <hipblaslt/hipblaslt.h>
#include <hip/hip_fp16.h>
#include <cuda_adapter.h>
# ifndef HAVE_HIP
#  error "Not found ROCm HIP envrioment, but use HIP"
# endif
#else /* fallback to CUDA */
/**
 * macro:
 * - CUDA_VERSION
 *   12020: V12.2.140
 */
#include <nvrtc.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cublas.h>
#include <cublasLt.h>
#include <cufft.h>
#include <curand.h>
#define DISABLE_CUSPARSE_DEPRECATED	1
#include <cusparse.h>
#endif

#endif /* __FAKECUDA_COMPAT */
