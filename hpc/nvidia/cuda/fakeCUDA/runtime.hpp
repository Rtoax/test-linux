// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * Refs:
 * - https://github.com/ROCm/rocm-systems.git
 */
#include <sys/types.h>
#include "compat.hpp"
#include "device.h"
#include "debug.h"
#include "types.h"


#if defined(__USE_HPCC__)
#define __cudaGetKernel	__hcGetKernel
#define __cudaLaunchKernel	__hcLaunchKernel
#define __cudaPopCallConfiguration	__hcPopCallConfiguration
#define __cudaPushCallConfiguration	__hcPushCallConfiguration
#define __cudaRegisterFatBinary	__hcRegisterFatBinary
#define __cudaRegisterFatBinaryEnd	__hcRegisterFatBinaryEnd
#define __cudaRegisterFunction	__hcRegisterFunction
#define __cudaRegisterVar	__hcRegisterVar
#define __cudaUnregisterFatBinary	__hcUnregisterFatBinary
#elif defined(__USE_HIP__)
#define __cudaGetKernel	__hipGetKernel
#define __cudaLaunchKernel	__hipLaunchKernel
#define __cudaPopCallConfiguration	__hipPopCallConfiguration
#define __cudaPushCallConfiguration	__hipPushCallConfiguration
#define __cudaRegisterFatBinary	__hipRegisterFatBinary
#define __cudaRegisterFatBinaryEnd	__hipRegisterFatBinaryEnd
#define __cudaRegisterFunction	__hipRegisterFunction
#define __cudaRegisterVar	__hipRegisterVar
#define __cudaUnregisterFatBinary	__hipUnregisterFatBinary
#endif


#ifdef __cplusplus
extern "C" {
#endif

char __cudaInitModule(void **fatCubinHandle);
void **__cudaRegisterFatBinary(void *fatCubin);
void __cudaRegisterFatBinaryEnd(void **fatCubinHandle);
void __cudaUnregisterFatBinary(void **fatCubinHandle);
void __cudaRegisterFunction(void **fatCubinHandle, const char *hostFun,
			    char *deviceFun, const char *deviceName,
			    int thread_limit, uint3 *tid, uint3 *bid,
			    dim3 *bDim, dim3 *gDim, int *wSize);
void __cudaRegisterVar(void **fatCubinHandle, char *hostVar,
		       char *deviceAddress, const char *deviceName,
		       int ext, size_t size, int constant, int global);
#if defined(__USE_HPCC__)
hcError_t __hcRegisterManagedVar(void *fatCubinHandle, void **hostVarPtrAddress,
				 void *deviceAddress, const char *deviceName,
				 size_t size, unsigned int align);
#else
void __cudaRegisterManagedVar(void **fatCubinHandle, void **hostVarPtrAddress,
			      char *deviceAddress, const char *deviceName,
			      int ext, size_t size, int constant, int global);
#endif

#if defined(__USE_HIP__)
hipError_t
#else
unsigned
#endif
__cudaPushCallConfiguration(dim3 gridDim, dim3 blockDim, size_t sharedMem,
			    cudaStream_t stream);
cudaError_t __cudaGetKernel(cudaKernel_t *kernel, const void *v);
cudaError_t __cudaPopCallConfiguration(dim3 *gridDim, dim3 *blockDim,
				       size_t *sharedMem,
				       #if defined(__USE_HIP__)
				       cudaStream_t *stream
				       #else
				       void *stream
				       #endif
				      );
cudaError_t __cudaLaunchKernel(cudaKernel_t kernel, dim3 gridDim, dim3 blockDim,
			       void **args, size_t sharedMem,
			       cudaStream_t stream);

cudaError_t cudaMalloc(void **devPtr, size_t size);
cudaError_t cudaMallocManaged(void **devPtr, size_t size, unsigned int flags);
cudaError_t cudaFree(void *devPtr);
cudaError_t cudaMemAdvise(const void *devPtr, size_t count,
			  cudaMemoryAdvise advice,
			  #if defined(__USE_HPCC__) || defined(__USE_HIP__) || CUDA_VERSION <= 12020
			  int device
			  #else
			  cudaMemLocation location
			  #endif
			  );
cudaError_t cudaMemset(void *devPtr, int value, size_t count);
cudaError_t cudaMemcpy(void *dst, const void *src, size_t count,
		       cudaMemcpyKind kind);

cudaError_t cudaSetDevice(int device);
cudaError_t cudaGetDevice(int *device);
cudaError_t cudaGetLastError();
const char *cudaGetErrorString(cudaError_t error);
cudaError_t cudaGetDeviceCount(int *count);
cudaError_t cudaDeviceSetLimit(cudaLimit limit, size_t value);
cudaError_t cudaGetDeviceProperties(cudaDeviceProp *prop, int device);
cudaError_t cudaGetDeviceProperties_v2(cudaDeviceProp *prop, int device);
cudaError_t cudaDeviceGetAttribute(int *value, cudaDeviceAttr attr, int device);
cudaError_t cudaDeviceDisablePeerAccess(int peerDevice);
cudaError_t cudaDeviceCanAccessPeer(int *canAccessPeer, int device, int peerDevice);
cudaError_t cudaDeviceGetP2PAttribute(int *value, enum cudaDeviceP2PAttr attr,
				      int srcDevice, int dstDevice);
cudaError_t cudaDeviceSynchronize();
cudaError_t cudaStreamCreate(cudaStream_t *pStream);
cudaError_t cudaStreamDestroy(cudaStream_t stream);
cudaError_t cudaStreamSynchronize(cudaStream_t stream);
cudaError_t cudaLaunchKernel(const void *func, dim3 gridDim, dim3 blockDim,
			     void **args, size_t sharedMem, cudaStream_t stream);
cudaError_t cudaLaunchCooperativeKernel(const void *func,
					dim3 gridDim, dim3 blockDim,
					void **args,
					#if defined(__USE_HPCC__) || defined(__USE_HIP__)
					unsigned int sharedMem,
					#else
					size_t sharedMem,
					#endif
					cudaStream_t stream);

cudaError_t cudaEventCreate(cudaEvent_t *event);
cudaError_t cudaEventCreateWithFlags(cudaEvent_t *event, unsigned int flags);
cudaError_t cudaEventDestroy(cudaEvent_t event);
cudaError_t cudaEventElapsedTime(float *ms, cudaEvent_t start, cudaEvent_t end);
cudaError_t cudaEventQuery(cudaEvent_t event);
cudaError_t cudaEventRecord(cudaEvent_t event, cudaStream_t stream);
cudaError_t cudaEventRecordWithFlags(cudaEvent_t event, cudaStream_t stream,
				     unsigned int flags);
cudaError_t cudaEventSynchronize(cudaEvent_t event);

#ifdef __cplusplus
}
#endif
