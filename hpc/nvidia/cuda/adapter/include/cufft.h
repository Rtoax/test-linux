// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
#ifndef __CUDA_ADAPTER_FFT_H
#define __CUDA_ADAPTER_FFT_H 1

#ifdef _CUFFT_H_
#error "CudaAdapter not allow include origin CUDA cufft.h"
#endif

#include "wrapper_defs.h"

#define cufftResult cuX(fftResult)
#define CUFFT_SUCCESS CUX(FFT_SUCCESS)
#define CUFFT_INVALID_PLAN CUX(FFT_INVALID_PLAN)
#define CUFFT_ALLOC_FAILED CUX(FFT_ALLOC_FAILED)
#define CUFFT_INVALID_TYPE CUX(FFT_INVALID_TYPE)
#define CUFFT_INVALID_VALUE CUX(FFT_INVALID_VALUE)
#define CUFFT_INTERNAL_ERROR CUX(FFT_INTERNAL_ERROR)
#define CUFFT_EXEC_FAILED CUX(FFT_EXEC_FAILED)
#define CUFFT_SETUP_FAILED CUX(FFT_SETUP_FAILED)
#define CUFFT_INVALID_SIZE CUX(FFT_INVALID_SIZE)
#define CUFFT_UNALIGNED_DATA CUX(FFT_UNALIGNED_DATA)
#define CUFFT_INCOMPLETE_PARAMETER_LIST CUX(FFT_INCOMPLETE_PARAMETER_LIST)
#define CUFFT_INVALID_DEVICE CUX(FFT_INVALID_DEVICE)
#define CUFFT_PARSE_ERROR CUX(FFT_PARSE_ERROR)
#define CUFFT_NO_WORKSPACE CUX(FFT_NO_WORKSPACE)
#define CUFFT_NOT_IMPLEMENTED CUX(FFT_NOT_IMPLEMENTED)
#define CUFFT_LICENSE_ERROR CUX(FFT_LICENSE_ERROR)
#define CUFFT_NOT_SUPPORTED CUX(FFT_NOT_SUPPORTED)

/**
 * CUDA:
 * typedef enum libraryPropertyType_t {
 *     MAJOR_VERSION,
 *     MINOR_VERSION,
 *     PATCH_LEVEL
 * } libraryPropertyType;
 * hipfftResult hipfftGetProperty(hipfftLibraryPropertyType type, int* value);
 *
 * HIP:
 * typedef enum hipLibraryPropertyType {
 *     HIP_LIBRARY_MAJOR_VERSION,
 *     HIP_LIBRARY_MINOR_VERSION,
 *     HIP_LIBRARY_PATCH_LEVEL
 * } hipLibraryPropertyType;
 *
 * typedef enum hipfftLibraryPropertyType_t {
 *     HIPFFT_MAJOR_VERSION,
 *     HIPFFT_MINOR_VERSION,
 *     HIPFFT_PATCH_LEVEL
 * } hipfftLibraryPropertyType;
 *
 * cufftResult CUFFTAPI cufftGetProperty(libraryPropertyType type, int *value);
 */
#define cufftGetProperty(v, pval) cuX(fftGetProperty(v, pval))

#ifdef __USE_HPCC__
# include <hcfft/hcfft.h>
#elif defined(__USE_LUCA__)
# include <lcfft/lcfft.h>
#elif defined(__USE_HIP__)
# include <hipfft/hipfft.h>
#endif

#endif
