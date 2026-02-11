// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
#ifndef __CUDA_ADAPTER_FFT_H
#define __CUDA_ADAPTER_FFT_H 1

#include "wrapper_defs.h"

#define cufftResult __cu(fftResult)
#define CUFFT_SUCCESS __CU(FFT_SUCCESS)
#define CUFFT_INVALID_PLAN __CU(FFT_INVALID_PLAN)
#define CUFFT_ALLOC_FAILED __CU(FFT_ALLOC_FAILED)
#define CUFFT_INVALID_TYPE __CU(FFT_INVALID_TYPE)
#define CUFFT_INVALID_VALUE __CU(FFT_INVALID_VALUE)
#define CUFFT_INTERNAL_ERROR __CU(FFT_INTERNAL_ERROR)
#define CUFFT_EXEC_FAILED __CU(FFT_EXEC_FAILED)
#define CUFFT_SETUP_FAILED __CU(FFT_SETUP_FAILED)
#define CUFFT_INVALID_SIZE __CU(FFT_INVALID_SIZE)
#define CUFFT_UNALIGNED_DATA __CU(FFT_UNALIGNED_DATA)
#define CUFFT_INCOMPLETE_PARAMETER_LIST __CU(FFT_INCOMPLETE_PARAMETER_LIST)
#define CUFFT_INVALID_DEVICE __CU(FFT_INVALID_DEVICE)
#define CUFFT_PARSE_ERROR __CU(FFT_PARSE_ERROR)
#define CUFFT_NO_WORKSPACE __CU(FFT_NO_WORKSPACE)
#define CUFFT_NOT_IMPLEMENTED __CU(FFT_NOT_IMPLEMENTED)
#define CUFFT_LICENSE_ERROR __CU(FFT_LICENSE_ERROR)
#define CUFFT_NOT_SUPPORTED __CU(FFT_NOT_SUPPORTED)

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
#define cufftGetProperty(v, pval) __cu(fftGetProperty(v, pval))

#endif
