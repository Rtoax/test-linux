// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
/******************************************************************************\
 *             PTI - CUDA Profiling Tools Interface                           *
\******************************************************************************/
#ifndef __CUDA_ADAPTER_PTI_H
#define __CUDA_ADAPTER_PTI_H 1

#ifdef _CUPTI_H_
#error "CudaAdapter not allow include origin CUDA cupti.h"
#endif

#include "wrapper_defs.h"
#include "cupti_version.h"

#define CUpti_SubscriberHandle CUX(pti_SubscriberHandle)
#define CUpti_CallbackDomain CUX(pti_CallbackDomain)
#define CUpti_CallbackId CUX(pti_CallbackId)
#define CUpti_CallbackData CUX(pti_CallbackData)

/**
 * CUptiResult cuptiGetCallbackName(CUpti_CallbackDomain domain,
 *                                  uint32_t cbid, const char **name)
 */
#define cuptiGetCallbackName cuX(ptiGetCallbackName)

#define CUptiResult CUX(ptiResult)
#define CUPTI_SUCCESS CUX(PTI_SUCCESS)
#define cuptiGetResultString(n, pstr) cuX(ptiGetResultString(n, pstr))

/**
 * CUptiResult cuptiSubscribe(CUpti_SubscriberHandle *subscriber,
 *                            CUpti_CallbackFunc callback,
 *                            void *userdata);
 *
 * CUptiResult cuptiSubscribe_v2(CUpti_SubscriberHandle *subscriber,
 *                               CUpti_CallbackFunc callback,
 *                               void *userdata,
 *                               CUpti_SubscriberParams *pParams)
 */
#define cuptiSubscribe(s, c, u) cuX(ptiSubscribe(s, c, u))
#define cuptiSubscribe_v2 cuX(ptiSubscribe_v2)

/**
 * CUptiResult cuptiUnsubscribe(CUpti_SubscriberHandle subscriber);
 */
#define cuptiUnsubscribe(s) cuX(ptiUnsubscribe(s))

/**
 * CUptiResult cuptiEnableDomain(uint32_t enable,
 *                               CUpti_SubscriberHandle subscriber,
 *                               CUpti_CallbackDomain domain);
 */
#define cuptiEnableDomain(e, s, d) cuX(ptiEnableDomain(e, s, d))

/**
 * CUptiResult cuptiEnableAllDomains(uint32_t enable, CUpti_SubscriberHandle subscriber)
 */
#define cuptiEnableAllDomains cuX(ptiEnableAllDomains)

/**
 * CUptiResult cuptiSupportedDomains(size_t *domainCount,
 *                                   CUpti_DomainTable *domainTable)
 */
#define cuptiSupportedDomains cuX(ptiSupportedDomains)

/**
 * CUptiResult cuptiEnableCallback(uint32_t enable,
 *                                 CUpti_SubscriberHandle subscriber,
 *                                 CUpti_CallbackDomain domain,
 *                                 CUpti_CallbackId cbid)
 */
#define cuptiEnableCallback cuX(ptiEnableCallback)

/**
 * CUptiResult cuptiGetCallbackState(uint32_t *enable,
 *                                   CUpti_SubscriberHandle subscriber,
 *                                   CUpti_CallbackDomain domain,
 *                                   CUpti_CallbackId cbid)
 */
#define cuptiGetCallbackState cuX(ptiGetCallbackState)

#define CUPTI_CB_DOMAIN_INVALID CUX(PTI_CB_DOMAIN_INVALID)
#define CUPTI_CB_DOMAIN_DRIVER_API CUX(PTI_CB_DOMAIN_DRIVER_API)
#define CUPTI_CB_DOMAIN_RUNTIME_API CUX(PTI_CB_DOMAIN_RUNTIME_API)
#define CUPTI_CB_DOMAIN_RESOURCE CUX(PTI_CB_DOMAIN_RESOURCE)
#define CUPTI_CB_DOMAIN_SYNCHRONIZE CUX(PTI_CB_DOMAIN_SYNCHRONIZE)
#define CUPTI_CB_DOMAIN_NVTX CUX(PTI_CB_DOMAIN_NVTX)
#define CUPTI_CB_DOMAIN_STATE CUX(PTI_CB_DOMAIN_STATE)
#define CUPTI_CB_DOMAIN_SIZE CUX(PTI_CB_DOMAIN_SIZE)
#define CUPTI_CB_DOMAIN_FORCE_INT CUX(PTI_CB_DOMAIN_FORCE_INT)

#define CUPTI_API_ENTER CUX(PTI_API_ENTER)

#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy_v3020 \
	CUXcudaX(PTI_RUNTIME_TRACE_CBID_, Memcpy)
#define cudaMemcpy_v3020_params cudaX(Memcpy_params)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMalloc_v3020 \
	CUXcudaX(PTI_RUNTIME_TRACE_CBID_, Malloc)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLaunchKernel_v7000 \
	CUXcudaX(PTI_RUNTIME_TRACE_CBID_, LaunchKernel)
/**
 * CUDA 13.0
 * typedef struct cudaLaunchKernel_v7000_params_st {
 *   const void *func;
 *   dim3 gridDim;
 *   dim3 blockDim;
 *   void **args;
 *   size_t sharedMem;
 *   cudaStream_t stream;
 * } cudaLaunchKernel_v7000_params;
 *
 * LUCA 3.2.1
 * typedef struct lcLaunchKernel_params_st {
 *   const void* function_address;
 *   dim3 numBlocks;
 *   dim3 dimBlocks;
 *   void** args;
 *   void* args__val;
 *   size_t sharedMemBytes;
 *   lcStream_t stream;
 * } lcLaunchKernel_params;
 */
#define cudaLaunchKernel_v7000_params cudaX(LaunchKernel_params)

/**
 * CUDA 13:
 * typedef struct cudaMalloc_v3020_params_st {
 *   void **devPtr;
 *   size_t size;
 * } cudaMalloc_v3020_params;
 *
 * LUCA:
 * typedef struct lcMalloc_params_st {
 *   void** ptr;
 *   void* ptr__val;
 *   size_t bytesize;
 * } lcMalloc_params;
 */
#define cudaMalloc_v3020_params cudaX(Malloc_params)

#define CUcontext CUX(context)

/**
 * CUDA <= 12020:
 * CUresult cuCtxCreate_v2(CUcontext *pctx, unsigned int flags, CUdevice dev);
 *
 * CUDA > 12020:
 * CUresult cuCtxCreate_v3(CUcontext *pctx, CUexecAffinityParam *paramsArray,
 *                         int numParams, unsigned int flags, CUdevice dev);
 */
#define cuCtxCreate cuX(CtxCreate)
#define cuCtxDestroy cuX(CtxDestroy)

/**
 * LUCA: lcError_t lcCtxSynchronize();
 */
#define cuCtxSynchronize cuX(CtxSynchronize)

#define CUpti_Activity CUX(pti_Activity)
#define CUpti_ActivityKernel CUX(pti_ActivityKernel)
#define CUpti_ActivityKernel1 CUX(pti_ActivityKernel1)
#define CUpti_ActivityKernel2 CUX(pti_ActivityKernel2)
#define CUpti_ActivityKernel3 CUX(pti_ActivityKernel3)
#define CUpti_ActivityKernel4 CUX(pti_ActivityKernel4)
#define CUpti_ActivityKernel5 CUX(pti_ActivityKernel5)
#define CUpti_ActivityKernel6 CUX(pti_ActivityKernel6)
#define CUpti_ActivityKernel7 CUX(pti_ActivityKernel7)
#define CUpti_ActivityKernel8 CUX(pti_ActivityKernel8)
#define CUpti_ActivityKernel9 CUX(pti_ActivityKernel9)
#define CUpti_ActivityKernel10 CUX(pti_ActivityKernel10)

#define cuptiActivityRegisterCallbacks cuX(ptiActivityRegisterCallbacks)
#define cuptiActivityEnable cuX(ptiActivityEnable)
#define cuptiActivityFlushAll cuX(ptiActivityFlushAll)
#define cuptiActivityDisable cuX(ptiActivityDisable)
#define cuptiActivityGetNextRecord cuX(ptiActivityGetNextRecord)

#define CUPTI_ACTIVITY_KIND_INVALID CUX(PTI_ACTIVITY_KIND_INVALID)
#define CUPTI_ACTIVITY_KIND_MEMCPY CUX(PTI_ACTIVITY_KIND_MEMCPY)
#define CUPTI_ACTIVITY_KIND_MEMSET CUX(PTI_ACTIVITY_KIND_MEMSET)
#define CUPTI_ACTIVITY_KIND_KERNEL CUX(PTI_ACTIVITY_KIND_KERNEL)
#define CUPTI_ACTIVITY_KIND_DRIVER CUX(PTI_ACTIVITY_KIND_DRIVER)
#define CUPTI_ACTIVITY_KIND_RUNTIME CUX(PTI_ACTIVITY_KIND_RUNTIME)
#define CUPTI_ACTIVITY_KIND_EVENT CUX(PTI_ACTIVITY_KIND_EVENT)
#define CUPTI_ACTIVITY_KIND_METRIC CUX(PTI_ACTIVITY_KIND_METRIC)
#define CUPTI_ACTIVITY_KIND_DEVICE CUX(PTI_ACTIVITY_KIND_DEVICE)
#define CUPTI_ACTIVITY_KIND_CONTEXT CUX(PTI_ACTIVITY_KIND_CONTEXT)
#define CUPTI_ACTIVITY_KIND_CONCURRENT_KERNEL \
	CUX(PTI_ACTIVITY_KIND_CONCURRENT_KERNEL)
#define CUPTI_ACTIVITY_KIND_NAME CUX(PTI_ACTIVITY_KIND_NAME)
#define CUPTI_ACTIVITY_KIND_MARKER CUX(PTI_ACTIVITY_KIND_MARKER)
#define CUPTI_ACTIVITY_KIND_MARKER_DATA CUX(PTI_ACTIVITY_KIND_MARKER_DATA)
#define CUPTI_ACTIVITY_KIND_SOURCE_LOCATOR \
	CUX(PTI_ACTIVITY_KIND_SOURCE_LOCATOR)
#define CUPTI_ACTIVITY_KIND_GLOBAL_ACCESS CUX(PTI_ACTIVITY_KIND_GLOBAL_ACCESS)
#define CUPTI_ACTIVITY_KIND_BRANCH CUX(PTI_ACTIVITY_KIND_BRANCH)
#define CUPTI_ACTIVITY_KIND_OVERHEAD CUX(PTI_ACTIVITY_KIND_OVERHEAD)
#define CUPTI_ACTIVITY_KIND_CDP_KERNEL CUX(PTI_ACTIVITY_KIND_CDP_KERNEL)
#define CUPTI_ACTIVITY_KIND_PREEMPTION CUX(PTI_ACTIVITY_KIND_PREEMPTION)
#define CUPTI_ACTIVITY_KIND_ENVIRONMENT CUX(PTI_ACTIVITY_KIND_ENVIRONMENT)
#define CUPTI_ACTIVITY_KIND_EVENT_INSTANCE \
	CUX(PTI_ACTIVITY_KIND_EVENT_INSTANCE)
#define CUPTI_ACTIVITY_KIND_MEMCPY2 CUX(PTI_ACTIVITY_KIND_MEMCPY2)
#define CUPTI_ACTIVITY_KIND_METRIC_INSTANCE \
	CUX(PTI_ACTIVITY_KIND_METRIC_INSTANCE)
#define CUPTI_ACTIVITY_KIND_INSTRUCTION_EXECUTION \
	CUX(PTI_ACTIVITY_KIND_INSTRUCTION_EXECUTION)
#define CUPTI_ACTIVITY_KIND_UNIFIED_MEMORY_COUNTER \
	CUX(PTI_ACTIVITY_KIND_UNIFIED_MEMORY_COUNTER)
#define CUPTI_ACTIVITY_KIND_FUNCTION CUX(PTI_ACTIVITY_KIND_FUNCTION)
#define CUPTI_ACTIVITY_KIND_MODULE CUX(PTI_ACTIVITY_KIND_MODULE)
#define CUPTI_ACTIVITY_KIND_DEVICE_ATTRIBUTE \
	CUX(PTI_ACTIVITY_KIND_DEVICE_ATTRIBUTE)
#define CUPTI_ACTIVITY_KIND_SHARED_ACCESS CUX(PTI_ACTIVITY_KIND_SHARED_ACCESS)
#define CUPTI_ACTIVITY_KIND_PC_SAMPLING CUX(PTI_ACTIVITY_KIND_PC_SAMPLING)
#define CUPTI_ACTIVITY_KIND_PC_SAMPLING_RECORD_INFO \
	CUX(PTI_ACTIVITY_KIND_PC_SAMPLING_RECORD_INFO)
#define CUPTI_ACTIVITY_KIND_INSTRUCTION_CORRELATION \
	CUX(PTI_ACTIVITY_KIND_INSTRUCTION_CORRELATION)
#define CUPTI_ACTIVITY_KIND_OPENACC_DATA CUX(PTI_ACTIVITY_KIND_OPENACC_DATA)
#define CUPTI_ACTIVITY_KIND_OPENACC_LAUNCH \
	CUX(PTI_ACTIVITY_KIND_OPENACC_LAUNCH)
#define CUPTI_ACTIVITY_KIND_OPENACC_OTHER CUX(PTI_ACTIVITY_KIND_OPENACC_OTHER)
#define CUPTI_ACTIVITY_KIND_CUDA_EVENT CUX(PTI_ACTIVITY_KIND_CUDA_EVENT)
#define CUPTI_ACTIVITY_KIND_STREAM CUX(PTI_ACTIVITY_KIND_STREAM)
#define CUPTI_ACTIVITY_KIND_SYNCHRONIZATION \
	CUX(PTI_ACTIVITY_KIND_SYNCHRONIZATION)
#define CUPTI_ACTIVITY_KIND_EXTERNAL_CORRELATION \
	CUX(PTI_ACTIVITY_KIND_EXTERNAL_CORRELATION)
#define CUPTI_ACTIVITY_KIND_NVLINK CUX(PTI_ACTIVITY_KIND_NVLINK)
#define CUPTI_ACTIVITY_KIND_INSTANTANEOUS_EVENT \
	CUX(PTI_ACTIVITY_KIND_INSTANTANEOUS_EVENT)
#define CUPTI_ACTIVITY_KIND_INSTANTANEOUS_EVENT_INSTANCE \
	CUX(PTI_ACTIVITY_KIND_INSTANTANEOUS_EVENT_INSTANCE)
#define CUPTI_ACTIVITY_KIND_INSTANTANEOUS_METRIC \
	CUX(PTI_ACTIVITY_KIND_INSTANTANEOUS_METRIC)
#define CUPTI_ACTIVITY_KIND_INSTANTANEOUS_METRIC_INSTANCE \
	CUX(PTI_ACTIVITY_KIND_INSTANTANEOUS_METRIC_INSTANCE)
#define CUPTI_ACTIVITY_KIND_MEMORY CUX(PTI_ACTIVITY_KIND_MEMORY)
#define CUPTI_ACTIVITY_KIND_PCIE CUX(PTI_ACTIVITY_KIND_PCIE)
#define CUPTI_ACTIVITY_KIND_OPENMP CUX(PTI_ACTIVITY_KIND_OPENMP)
#define CUPTI_ACTIVITY_KIND_INTERNAL_LAUNCH_API \
	CUX(PTI_ACTIVITY_KIND_INTERNAL_LAUNCH_API)
#define CUPTI_ACTIVITY_KIND_MEMORY2 CUX(PTI_ACTIVITY_KIND_MEMORY2)
#define CUPTI_ACTIVITY_KIND_MEMORY_POOL CUX(PTI_ACTIVITY_KIND_MEMORY_POOL)
#define CUPTI_ACTIVITY_KIND_GRAPH_TRACE CUX(PTI_ACTIVITY_KIND_GRAPH_TRACE)
#define CUPTI_ACTIVITY_KIND_JIT CUX(PTI_ACTIVITY_KIND_JIT)
#define CUPTI_ACTIVITY_KIND_DEVICE_GRAPH_TRACE \
	CUX(PTI_ACTIVITY_KIND_DEVICE_GRAPH_TRACE)
#define CUPTI_ACTIVITY_KIND_MEM_DECOMPRESS \
	CUX(PTI_ACTIVITY_KIND_MEM_DECOMPRESS)
#define CUPTI_ACTIVITY_KIND_COUNT CUX(PTI_ACTIVITY_KIND_COUNT)
#define CUPTI_ACTIVITY_KIND_FORCE_INT CUX(PTI_ACTIVITY_KIND_FORCE_INT)

/**
 * FIXME: LUCA not support PmSampling
 */
#define CUpti_PmSampling_Object CUX(pti_PmSampling_Object)
#define CUpti_PmSampling_CounterData_GetSampleInfo_Params \
	CUX(pti_PmSampling_CounterData_GetSampleInfo_Params)
#define CUpti_PmSampling_Enable_Params CUX(pti_PmSampling_Enable_Params)
#define CUpti_PmSampling_SetConfig_Params CUX(pti_PmSampling_SetConfig_Params)
#define CUpti_PmSampling_Start_Params CUX(pti_PmSampling_Start_Params)
#define CUpti_Profiler_Host_Initialize_Params \
	CUX(pti_Profiler_Host_Initialize_Params)
#define CUpti_Profiler_Host_Object CUX(pti_Profiler_Host_Object)
#define CUpti_Profiler_Host_ConfigAddMetrics_Params \
	CUX(pti_Profiler_Host_ConfigAddMetrics_Params)
#define CUpti_Profiler_Host_GetConfigImageSize_Params \
	CUX(pti_Profiler_Host_GetConfigImageSize_Params)
#define CUpti_Profiler_Host_GetConfigImage_Params \
	CUX(pti_Profiler_Host_GetConfigImage_Params)
#define CUpti_Profiler_Host_GetNumOfPasses_Params \
	CUX(pti_Profiler_Host_GetNumOfPasses_Params)
#define CUpti_Profiler_Host_Deinitialize_Params \
	CUX(pti_Profiler_Host_Deinitialize_Params)
#define CUpti_Profiler_Host_Object CUX(pti_Profiler_Host_Object)
#define CUpti_Profiler_Host_EvaluateToGpuValues_Params \
	CUX(pti_Profiler_Host_EvaluateToGpuValues_Params)
#define CUpti_Profiler_Host_Initialize_Params \
	CUX(pti_Profiler_Host_Initialize_Params)
#define CUpti_Profiler_Host_Object CUX(pti_Profiler_Host_Object)
#define CUpti_Profiler_Host_Deinitialize_Params \
	CUX(pti_Profiler_Host_Deinitialize_Params)
#define CUpti_Profiler_Initialize_Params CUX(pti_Profiler_Initialize_Params)
#define CUpti_Device_GetChipName_Params CUX(pti_Device_GetChipName_Params)

#ifdef __USE_HPCC__
# include <hcpti/hcpti.h>
#elif defined(__USE_LUCA__)
# ifdef LUCA_PHASE_II_PROJECT
#  include <lcpti/lcpti.h>
# else
#  include <hcpti/hcpti.h>
# endif
#elif defined(__USE_HIP__)
#endif

#endif
