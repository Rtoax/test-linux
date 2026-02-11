// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
/******************************************************************************\
 *             PTI - CUDA Profiling Tools Interface                           *
\******************************************************************************/
#ifndef __CUDA_ADAPTER_PTI_H
#define __CUDA_ADAPTER_PTI_H 1

#include "wrapper_defs.h"

#define CUPTI_API_VERSION __CU(PTI_API_VERSION)
/**
 * CUptiResult cuptiGetVersion(uint32_t *version);
 */
#define cuptiGetVersion __cu(ptiGetVersion)

#define CUpti_SubscriberHandle __CU(pti_SubscriberHandle)
#define CUpti_CallbackDomain __CU(pti_CallbackDomain)
#define CUpti_CallbackId __CU(pti_CallbackId)
#define CUpti_CallbackData __CU(pti_CallbackData)

/**
 * CUptiResult cuptiGetCallbackName(CUpti_CallbackDomain domain,
 *                                  uint32_t cbid, const char **name)
 */
#define cuptiGetCallbackName __cu(ptiGetCallbackName)

#define CUptiResult __CU(ptiResult)
#define CUPTI_SUCCESS __CU(PTI_SUCCESS)
#define cuptiGetResultString(n, pstr) __cu(ptiGetResultString(n, pstr))

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
#define cuptiSubscribe(s, c, u) __cu(ptiSubscribe(s, c, u))
#define cuptiSubscribe_v2 __cu(ptiSubscribe_v2)

/**
 * CUptiResult cuptiUnsubscribe(CUpti_SubscriberHandle subscriber);
 */
#define cuptiUnsubscribe(s) __cu(ptiUnsubscribe(s))

/**
 * CUptiResult cuptiEnableDomain(uint32_t enable,
 *                               CUpti_SubscriberHandle subscriber,
 *                               CUpti_CallbackDomain domain);
 */
#define cuptiEnableDomain(e, s, d) __cu(ptiEnableDomain(e, s, d))

/**
 * CUptiResult cuptiEnableAllDomains(uint32_t enable, CUpti_SubscriberHandle subscriber)
 */
#define cuptiEnableAllDomains __cu(ptiEnableAllDomains)

/**
 * CUptiResult cuptiSupportedDomains(size_t *domainCount,
 *                                   CUpti_DomainTable *domainTable)
 */
#define cuptiSupportedDomains __cu(ptiSupportedDomains)

/**
 * CUptiResult cuptiEnableCallback(uint32_t enable,
 *                                 CUpti_SubscriberHandle subscriber,
 *                                 CUpti_CallbackDomain domain,
 *                                 CUpti_CallbackId cbid)
 */
#define cuptiEnableCallback __cu(ptiEnableCallback)

/**
 * CUptiResult cuptiGetCallbackState(uint32_t *enable,
 *                                   CUpti_SubscriberHandle subscriber,
 *                                   CUpti_CallbackDomain domain,
 *                                   CUpti_CallbackId cbid)
 */
#define cuptiGetCallbackState __cu(ptiGetCallbackState)

#define CUPTI_CB_DOMAIN_INVALID __CU(PTI_CB_DOMAIN_INVALID)
#define CUPTI_CB_DOMAIN_DRIVER_API __CU(PTI_CB_DOMAIN_DRIVER_API)
#define CUPTI_CB_DOMAIN_RUNTIME_API __CU(PTI_CB_DOMAIN_RUNTIME_API)
#define CUPTI_CB_DOMAIN_RESOURCE __CU(PTI_CB_DOMAIN_RESOURCE)
#define CUPTI_CB_DOMAIN_SYNCHRONIZE __CU(PTI_CB_DOMAIN_SYNCHRONIZE)
#define CUPTI_CB_DOMAIN_NVTX __CU(PTI_CB_DOMAIN_NVTX)
#define CUPTI_CB_DOMAIN_STATE __CU(PTI_CB_DOMAIN_STATE)
#define CUPTI_CB_DOMAIN_SIZE __CU(PTI_CB_DOMAIN_SIZE)
#define CUPTI_CB_DOMAIN_FORCE_INT __CU(PTI_CB_DOMAIN_FORCE_INT)

#define CUPTI_API_ENTER __CU(PTI_API_ENTER)

#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy_v3020 \
	__CU_cuda(PTI_RUNTIME_TRACE_CBID_, Memcpy)
#define cudaMemcpy_v3020_params __cuda(Memcpy_params)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMalloc_v3020 \
	__CU_cuda(PTI_RUNTIME_TRACE_CBID_, Malloc)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLaunchKernel_v7000 \
	__CU_cuda(PTI_RUNTIME_TRACE_CBID_, LaunchKernel)
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
#define cudaLaunchKernel_v7000_params __cuda(LaunchKernel_params)

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
#define cudaMalloc_v3020_params __cuda(Malloc_params)

#define CUcontext __CU(context)
#define cuCtxCreate __cu(CtxCreate)
#define cuCtxDestroy __cu(CtxDestroy)

/**
 * LUCA: lcError_t lcCtxSynchronize();
 */
#define cuCtxSynchronize __cu(CtxSynchronize)

#define CUpti_Activity __CU(pti_Activity)
#define CUpti_ActivityKernel __CU(pti_ActivityKernel)
#define CUpti_ActivityKernel1 __CU(pti_ActivityKernel1)
#define CUpti_ActivityKernel2 __CU(pti_ActivityKernel2)
#define CUpti_ActivityKernel3 __CU(pti_ActivityKernel3)
#define CUpti_ActivityKernel4 __CU(pti_ActivityKernel4)
#define CUpti_ActivityKernel5 __CU(pti_ActivityKernel5)
#define CUpti_ActivityKernel6 __CU(pti_ActivityKernel6)
#define CUpti_ActivityKernel7 __CU(pti_ActivityKernel7)
#define CUpti_ActivityKernel8 __CU(pti_ActivityKernel8)
#define CUpti_ActivityKernel9 __CU(pti_ActivityKernel9)
#define CUpti_ActivityKernel10 __CU(pti_ActivityKernel10)

#define cuptiActivityRegisterCallbacks __cu(ptiActivityRegisterCallbacks)
#define cuptiActivityEnable __cu(ptiActivityEnable)
#define cuptiActivityFlushAll __cu(ptiActivityFlushAll)
#define cuptiActivityDisable __cu(ptiActivityDisable)
#define cuptiActivityGetNextRecord __cu(ptiActivityGetNextRecord)

#define CUPTI_ACTIVITY_KIND_INVALID __CU(PTI_ACTIVITY_KIND_INVALID)
#define CUPTI_ACTIVITY_KIND_MEMCPY __CU(PTI_ACTIVITY_KIND_MEMCPY)
#define CUPTI_ACTIVITY_KIND_MEMSET __CU(PTI_ACTIVITY_KIND_MEMSET)
#define CUPTI_ACTIVITY_KIND_KERNEL __CU(PTI_ACTIVITY_KIND_KERNEL)
#define CUPTI_ACTIVITY_KIND_DRIVER __CU(PTI_ACTIVITY_KIND_DRIVER)
#define CUPTI_ACTIVITY_KIND_RUNTIME __CU(PTI_ACTIVITY_KIND_RUNTIME)
#define CUPTI_ACTIVITY_KIND_EVENT __CU(PTI_ACTIVITY_KIND_EVENT)
#define CUPTI_ACTIVITY_KIND_METRIC __CU(PTI_ACTIVITY_KIND_METRIC)
#define CUPTI_ACTIVITY_KIND_DEVICE __CU(PTI_ACTIVITY_KIND_DEVICE)
#define CUPTI_ACTIVITY_KIND_CONTEXT __CU(PTI_ACTIVITY_KIND_CONTEXT)
#define CUPTI_ACTIVITY_KIND_CONCURRENT_KERNEL \
	__CU(PTI_ACTIVITY_KIND_CONCURRENT_KERNEL)
#define CUPTI_ACTIVITY_KIND_NAME __CU(PTI_ACTIVITY_KIND_NAME)
#define CUPTI_ACTIVITY_KIND_MARKER __CU(PTI_ACTIVITY_KIND_MARKER)
#define CUPTI_ACTIVITY_KIND_MARKER_DATA __CU(PTI_ACTIVITY_KIND_MARKER_DATA)
#define CUPTI_ACTIVITY_KIND_SOURCE_LOCATOR \
	__CU(PTI_ACTIVITY_KIND_SOURCE_LOCATOR)
#define CUPTI_ACTIVITY_KIND_GLOBAL_ACCESS __CU(PTI_ACTIVITY_KIND_GLOBAL_ACCESS)
#define CUPTI_ACTIVITY_KIND_BRANCH __CU(PTI_ACTIVITY_KIND_BRANCH)
#define CUPTI_ACTIVITY_KIND_OVERHEAD __CU(PTI_ACTIVITY_KIND_OVERHEAD)
#define CUPTI_ACTIVITY_KIND_CDP_KERNEL __CU(PTI_ACTIVITY_KIND_CDP_KERNEL)
#define CUPTI_ACTIVITY_KIND_PREEMPTION __CU(PTI_ACTIVITY_KIND_PREEMPTION)
#define CUPTI_ACTIVITY_KIND_ENVIRONMENT __CU(PTI_ACTIVITY_KIND_ENVIRONMENT)
#define CUPTI_ACTIVITY_KIND_EVENT_INSTANCE \
	__CU(PTI_ACTIVITY_KIND_EVENT_INSTANCE)
#define CUPTI_ACTIVITY_KIND_MEMCPY2 __CU(PTI_ACTIVITY_KIND_MEMCPY2)
#define CUPTI_ACTIVITY_KIND_METRIC_INSTANCE \
	__CU(PTI_ACTIVITY_KIND_METRIC_INSTANCE)
#define CUPTI_ACTIVITY_KIND_INSTRUCTION_EXECUTION \
	__CU(PTI_ACTIVITY_KIND_INSTRUCTION_EXECUTION)
#define CUPTI_ACTIVITY_KIND_UNIFIED_MEMORY_COUNTER \
	__CU(PTI_ACTIVITY_KIND_UNIFIED_MEMORY_COUNTER)
#define CUPTI_ACTIVITY_KIND_FUNCTION __CU(PTI_ACTIVITY_KIND_FUNCTION)
#define CUPTI_ACTIVITY_KIND_MODULE __CU(PTI_ACTIVITY_KIND_MODULE)
#define CUPTI_ACTIVITY_KIND_DEVICE_ATTRIBUTE \
	__CU(PTI_ACTIVITY_KIND_DEVICE_ATTRIBUTE)
#define CUPTI_ACTIVITY_KIND_SHARED_ACCESS __CU(PTI_ACTIVITY_KIND_SHARED_ACCESS)
#define CUPTI_ACTIVITY_KIND_PC_SAMPLING __CU(PTI_ACTIVITY_KIND_PC_SAMPLING)
#define CUPTI_ACTIVITY_KIND_PC_SAMPLING_RECORD_INFO \
	__CU(PTI_ACTIVITY_KIND_PC_SAMPLING_RECORD_INFO)
#define CUPTI_ACTIVITY_KIND_INSTRUCTION_CORRELATION \
	__CU(PTI_ACTIVITY_KIND_INSTRUCTION_CORRELATION)
#define CUPTI_ACTIVITY_KIND_OPENACC_DATA __CU(PTI_ACTIVITY_KIND_OPENACC_DATA)
#define CUPTI_ACTIVITY_KIND_OPENACC_LAUNCH \
	__CU(PTI_ACTIVITY_KIND_OPENACC_LAUNCH)
#define CUPTI_ACTIVITY_KIND_OPENACC_OTHER __CU(PTI_ACTIVITY_KIND_OPENACC_OTHER)
#define CUPTI_ACTIVITY_KIND_CUDA_EVENT __CU(PTI_ACTIVITY_KIND_CUDA_EVENT)
#define CUPTI_ACTIVITY_KIND_STREAM __CU(PTI_ACTIVITY_KIND_STREAM)
#define CUPTI_ACTIVITY_KIND_SYNCHRONIZATION \
	__CU(PTI_ACTIVITY_KIND_SYNCHRONIZATION)
#define CUPTI_ACTIVITY_KIND_EXTERNAL_CORRELATION \
	__CU(PTI_ACTIVITY_KIND_EXTERNAL_CORRELATION)
#define CUPTI_ACTIVITY_KIND_NVLINK __CU(PTI_ACTIVITY_KIND_NVLINK)
#define CUPTI_ACTIVITY_KIND_INSTANTANEOUS_EVENT \
	__CU(PTI_ACTIVITY_KIND_INSTANTANEOUS_EVENT)
#define CUPTI_ACTIVITY_KIND_INSTANTANEOUS_EVENT_INSTANCE \
	__CU(PTI_ACTIVITY_KIND_INSTANTANEOUS_EVENT_INSTANCE)
#define CUPTI_ACTIVITY_KIND_INSTANTANEOUS_METRIC \
	__CU(PTI_ACTIVITY_KIND_INSTANTANEOUS_METRIC)
#define CUPTI_ACTIVITY_KIND_INSTANTANEOUS_METRIC_INSTANCE \
	__CU(PTI_ACTIVITY_KIND_INSTANTANEOUS_METRIC_INSTANCE)
#define CUPTI_ACTIVITY_KIND_MEMORY __CU(PTI_ACTIVITY_KIND_MEMORY)
#define CUPTI_ACTIVITY_KIND_PCIE __CU(PTI_ACTIVITY_KIND_PCIE)
#define CUPTI_ACTIVITY_KIND_OPENMP __CU(PTI_ACTIVITY_KIND_OPENMP)
#define CUPTI_ACTIVITY_KIND_INTERNAL_LAUNCH_API \
	__CU(PTI_ACTIVITY_KIND_INTERNAL_LAUNCH_API)
#define CUPTI_ACTIVITY_KIND_MEMORY2 __CU(PTI_ACTIVITY_KIND_MEMORY2)
#define CUPTI_ACTIVITY_KIND_MEMORY_POOL __CU(PTI_ACTIVITY_KIND_MEMORY_POOL)
#define CUPTI_ACTIVITY_KIND_GRAPH_TRACE __CU(PTI_ACTIVITY_KIND_GRAPH_TRACE)
#define CUPTI_ACTIVITY_KIND_JIT __CU(PTI_ACTIVITY_KIND_JIT)
#define CUPTI_ACTIVITY_KIND_DEVICE_GRAPH_TRACE \
	__CU(PTI_ACTIVITY_KIND_DEVICE_GRAPH_TRACE)
#define CUPTI_ACTIVITY_KIND_MEM_DECOMPRESS \
	__CU(PTI_ACTIVITY_KIND_MEM_DECOMPRESS)
#define CUPTI_ACTIVITY_KIND_COUNT __CU(PTI_ACTIVITY_KIND_COUNT)
#define CUPTI_ACTIVITY_KIND_FORCE_INT __CU(PTI_ACTIVITY_KIND_FORCE_INT)

/**
 * FIXME: LUCA not support PmSampling
 */
#define CUpti_PmSampling_Object __CU(pti_PmSampling_Object)
#define CUpti_PmSampling_CounterData_GetSampleInfo_Params \
	__CU(pti_PmSampling_CounterData_GetSampleInfo_Params)
#define CUpti_PmSampling_Enable_Params __CU(pti_PmSampling_Enable_Params)
#define CUpti_PmSampling_SetConfig_Params __CU(pti_PmSampling_SetConfig_Params)
#define CUpti_PmSampling_Start_Params __CU(pti_PmSampling_Start_Params)
#define CUpti_Profiler_Host_Initialize_Params \
	__CU(pti_Profiler_Host_Initialize_Params)
#define CUpti_Profiler_Host_Object __CU(pti_Profiler_Host_Object)
#define CUpti_Profiler_Host_ConfigAddMetrics_Params \
	__CU(pti_Profiler_Host_ConfigAddMetrics_Params)
#define CUpti_Profiler_Host_GetConfigImageSize_Params \
	__CU(pti_Profiler_Host_GetConfigImageSize_Params)
#define CUpti_Profiler_Host_GetConfigImage_Params \
	__CU(pti_Profiler_Host_GetConfigImage_Params)
#define CUpti_Profiler_Host_GetNumOfPasses_Params \
	__CU(pti_Profiler_Host_GetNumOfPasses_Params)
#define CUpti_Profiler_Host_Deinitialize_Params \
	__CU(pti_Profiler_Host_Deinitialize_Params)
#define CUpti_Profiler_Host_Object __CU(pti_Profiler_Host_Object)
#define CUpti_Profiler_Host_EvaluateToGpuValues_Params \
	__CU(pti_Profiler_Host_EvaluateToGpuValues_Params)
#define CUpti_Profiler_Host_Initialize_Params \
	__CU(pti_Profiler_Host_Initialize_Params)
#define CUpti_Profiler_Host_Object __CU(pti_Profiler_Host_Object)
#define CUpti_Profiler_Host_Deinitialize_Params \
	__CU(pti_Profiler_Host_Deinitialize_Params)
#define CUpti_Profiler_Initialize_Params __CU(pti_Profiler_Initialize_Params)
#define CUpti_Device_GetChipName_Params __CU(pti_Device_GetChipName_Params)

#endif
