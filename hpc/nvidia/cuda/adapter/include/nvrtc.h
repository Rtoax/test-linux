// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
/******************************************************************************\
 *             RTC                                                            *
\******************************************************************************/
#ifndef __CUDA_ADAPTER_NVRTC_H
#define __CUDA_ADAPTER_NVRTC_H 1

#ifdef __NVRTC_H__
#error "CudaAdapter not allow include origin CUDA nvrtc.h"
#endif

#include "wrapper_defs.h"

#define nvrtcResult __nv(rtcResult)
#define NVRTC_SUCCESS __NV(RTC_SUCCESS)
#define NVRTC_ERROR_OUT_OF_MEMORY __NV(RTC_ERROR_OUT_OF_MEMORY)
#define NVRTC_ERROR_PROGRAM_CREATION_FAILURE \
	__NV(RTC_ERROR_PROGRAM_CREATION_FAILURE)
#define NVRTC_ERROR_INVALID_INPUT __NV(RTC_ERROR_INVALID_INPUT)
#define NVRTC_ERROR_INVALID_PROGRAM __NV(RTC_ERROR_INVALID_PROGRAM)
#define NVRTC_ERROR_INVALID_OPTION __NV(RTC_ERROR_INVALID_OPTION)
#define NVRTC_ERROR_COMPILATION __NV(RTC_ERROR_COMPILATION)
#define NVRTC_ERROR_BUILTIN_OPERATION_FAILURE \
	__NV(RTC_ERROR_BUILTIN_OPERATION_FAILURE)
#define NVRTC_ERROR_NO_NAME_EXPRESSIONS_AFTER_COMPILATION \
	__NV(RTC_ERROR_NO_NAME_EXPRESSIONS_AFTER_COMPILATION)
#define NVRTC_ERROR_NO_LOWERED_NAMES_BEFORE_COMPILATION \
	__NV(RTC_ERROR_NO_LOWERED_NAMES_BEFORE_COMPILATION)
#define NVRTC_ERROR_NAME_EXPRESSION_NOT_VALID \
	__NV(RTC_ERROR_NAME_EXPRESSION_NOT_VALID)
#define NVRTC_ERROR_INTERNAL_ERROR __NV(RTC_ERROR_INTERNAL_ERROR)
#define NVRTC_ERROR_TIME_FILE_WRITE_FAILED \
	__NV(RTC_ERROR_TIME_FILE_WRITE_FAILED)

#define nvrtcGetErrorString __nv(rtcGetErrorString)

#define nvrtcProgram __nv(rtcProgram)

/**
 * CUDA 13
 * nvrtcResult nvrtcCreateProgram(nvrtcProgram *prog,
 *                                const char *src,
 *                                const char *name,
 *                                int numHeaders,
 *                                const char * const *headers,
 *                                const char * const *includeNames);
 *
 * HIP
 * hiprtcResult hiprtcCreateProgram(hiprtcProgram* prog,
 *                                  const char* src,
 *                                  const char* name,
 *                                  int numHeaders,
 *                                  const char** headers,
 *                                  const char** includeNames);
 */
#define nvrtcCreateProgram __nv(rtcCreateProgram)

/**
 * CUDA 12:
 * nvrtcResult nvrtcDestroyProgram(nvrtcProgram *prog);
 *
 * HIP:
 * hiprtcResult hiprtcDestroyProgram(hiprtcProgram* prog);
 */
#define nvrtcDestroyProgram(prog) __nv(rtcDestroyProgram(prog))

/**
 * CUDA 12 and 13 don't have it?
 * HIP:
 * hiprtcResult hiprtcGetCode(hiprtcProgram prog, char* code);
 * hiprtcResult hiprtcGetCodeSize(hiprtcProgram prog, size_t* codeSizeRet);
 * hiprtcResult hiprtcGetBitcode(hiprtcProgram prog, char* bitcode);
 * hiprtcResult hiprtcGetBitcodeSize(hiprtcProgram prog, size_t* bitcode_size);
 */

/**
 * CUDA 12:
 * nvrtcResult nvrtcCompileProgram(nvrtcProgram prog,
 *                                 int numOptions, const char * const *options);
 * HIP:
 * hiprtcResult hiprtcCompileProgram(hiprtcProgram prog,
 *                                   int numOptions,
 *                                   const char** options);
 */
#define nvrtcCompileProgram(prog, numOptions, options) \
	__nv(rtcCompileProgram(prog, numOptions, options))

/**
 * CUDA 12:
 * nvrtcResult nvrtcGetProgramLog(nvrtcProgram prog, char *log);
 *
 * HIP:
 * hiprtcResult hiprtcGetProgramLog(hiprtcProgram prog, char* log);
 */
#define nvrtcGetProgramLog(prog, log) __nv(rtcGetProgramLog(prog, log))

/**
 * CUDA 13
 * nvrtcResult nvrtcGetProgramLogSize(nvrtcProgram prog, size_t *logSizeRet);
 *
 * HIP
 * hiprtcResult hiprtcGetProgramLogSize(hiprtcProgram prog, size_t* logSizeRet);
 */
#define nvrtcGetProgramLogSize __nv(rtcGetProgramLogSize)

#define nvrtcGetPTXSize __nv(rtcGetPTXSize)
#define nvrtcGetPTX __nv(rtcGetPTX)

/**
 * WARNING: cuda don't has Bitcode functions, this use to normalize development.
 * LUCA/HPCC like ROCm HIP, thus, just define HIP here.
 */
#define hiprtcGetBitcodeSize __nv(rtcGetBitcodeSize)
#define hiprtcGetBitcode __nv(rtcGetBitcode)

#ifdef __USE_HPCC__
# include <hcr/hcrtc.h>
#elif defined(__USE_LUCA__)
# ifdef LUCA_PHASE_II_PROJECT
#  include <lcr/lcrtc.h>
# else
#  include <hcr/hcrtc.h>
# endif
#elif defined(__USE_HIP__)
# include <hip/hiprtc.h>
#endif

#endif
