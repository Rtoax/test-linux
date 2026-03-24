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

#define nvrtcResult nvX(rtcResult)
#define NVRTC_SUCCESS NVX(RTC_SUCCESS)
#define NVRTC_ERROR_OUT_OF_MEMORY NVX(RTC_ERROR_OUT_OF_MEMORY)
#define NVRTC_ERROR_PROGRAM_CREATION_FAILURE \
	NVX(RTC_ERROR_PROGRAM_CREATION_FAILURE)
#define NVRTC_ERROR_INVALID_INPUT NVX(RTC_ERROR_INVALID_INPUT)
#define NVRTC_ERROR_INVALID_PROGRAM NVX(RTC_ERROR_INVALID_PROGRAM)
#define NVRTC_ERROR_INVALID_OPTION NVX(RTC_ERROR_INVALID_OPTION)
#define NVRTC_ERROR_COMPILATION NVX(RTC_ERROR_COMPILATION)
#define NVRTC_ERROR_BUILTIN_OPERATION_FAILURE \
	NVX(RTC_ERROR_BUILTIN_OPERATION_FAILURE)
#define NVRTC_ERROR_NO_NAME_EXPRESSIONS_AFTER_COMPILATION \
	NVX(RTC_ERROR_NO_NAME_EXPRESSIONS_AFTER_COMPILATION)
#define NVRTC_ERROR_NO_LOWERED_NAMES_BEFORE_COMPILATION \
	NVX(RTC_ERROR_NO_LOWERED_NAMES_BEFORE_COMPILATION)
#define NVRTC_ERROR_NAME_EXPRESSION_NOT_VALID \
	NVX(RTC_ERROR_NAME_EXPRESSION_NOT_VALID)
#define NVRTC_ERROR_INTERNAL_ERROR NVX(RTC_ERROR_INTERNAL_ERROR)
#define NVRTC_ERROR_TIME_FILE_WRITE_FAILED \
	NVX(RTC_ERROR_TIME_FILE_WRITE_FAILED)

#define nvrtcGetErrorString nvX(rtcGetErrorString)

#define nvrtcProgram nvX(rtcProgram)

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
#define nvrtcCreateProgram nvX(rtcCreateProgram)

/**
 * CUDA 12:
 * nvrtcResult nvrtcDestroyProgram(nvrtcProgram *prog);
 *
 * HIP:
 * hiprtcResult hiprtcDestroyProgram(hiprtcProgram* prog);
 */
#define nvrtcDestroyProgram(prog) nvX(rtcDestroyProgram(prog))

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
	nvX(rtcCompileProgram(prog, numOptions, options))

/**
 * CUDA 12:
 * nvrtcResult nvrtcGetProgramLog(nvrtcProgram prog, char *log);
 *
 * HIP:
 * hiprtcResult hiprtcGetProgramLog(hiprtcProgram prog, char* log);
 */
#define nvrtcGetProgramLog(prog, log) nvX(rtcGetProgramLog(prog, log))

/**
 * CUDA 13
 * nvrtcResult nvrtcGetProgramLogSize(nvrtcProgram prog, size_t *logSizeRet);
 *
 * HIP
 * hiprtcResult hiprtcGetProgramLogSize(hiprtcProgram prog, size_t* logSizeRet);
 */
#define nvrtcGetProgramLogSize nvX(rtcGetProgramLogSize)

#define nvrtcGetPTXSize nvX(rtcGetPTXSize)
#define nvrtcGetPTX nvX(rtcGetPTX)

/**
 * WARNING: cuda don't has Bitcode functions, this use to normalize development.
 * LUCA/HPCC like ROCm HIP, thus, just define HIP here.
 */
#define hiprtcGetBitcodeSize nvX(rtcGetBitcodeSize)
#define hiprtcGetBitcode nvX(rtcGetBitcode)

#ifdef __USE_HPCC__
# include <hcr/hcrtc.h>
#elif defined(__USE_LUCA__)
# include <lcr/lcrtc.h>
#elif defined(__USE_HIP__)
# include <hip/hiprtc.h>
#endif

#endif
