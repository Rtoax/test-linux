// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * Refs:
 * - https://github.com/ROCm/rocm-systems.git
 */
#ifdef HAVE_HPCC
#include <hc_runtime.h>
#include <hcc/hcc_internal.h>
#include <cuda_adapter.h>
#else
#include <cuda.h>
#include <cuda_runtime.h>
#endif
#include <sys/types.h>

#include "debug.h"
#include "types.h"


static unsigned __hipFatMAGIC2 = 0x48495046;  // "HIPF"
static unsigned __cudaFatMAGIC2 = 0x466243b1;

/**
 * /usr/local/cuda-13.0/targets/x86_64-linux/include/driver_types.h
 * typedef __device_builtin__ struct CUkern_st *cudaKernel_t;
 */
struct CUkern_st {
};

/**
 * https://github.com/ROCm/rocm-systems.git
 * clr/hipamd/src/hip_platform.cpp
 */
struct __CudaFatBinaryWrapper {
	unsigned int magic;
	unsigned int version;
	void *binary;
	void *dummy1;
};

#ifdef __cplusplus
extern "C" {
#endif
/**
 * - https://github.com/ROCm/rocm-systems.git
 *   void** __hipRegisterFatBinary(const void* data);
 */
void **__cudaRegisterFatBinary(void *fatCubin)
{
	struct __CudaFatBinaryWrapper *wrapper = (struct __CudaFatBinaryWrapper *)fatCubin;
	LOG_DEBUG("fatCubin %p, magic 0x%x(%c%c%c%c), version %d, binary %p\n",
		  fatCubin, wrapper->magic,
		  (wrapper->magic >> 24) & 0xff,
		  (wrapper->magic >> 16) & 0xff,
		  (wrapper->magic >> 8) & 0xff,
		  wrapper->magic & 0xff,
		  wrapper->version, wrapper->binary,
		  wrapper->dummy1);

	if ((wrapper->magic != __cudaFatMAGIC2 && wrapper->magic != __hipFatMAGIC2) ||
	    wrapper->version != 1) {
		LOG_ERROR("Cannot Register fat binary. FatMagic: %u version: %u\n",
			  wrapper->magic, wrapper->version);
	}

	return NULL;
}

void __cudaRegisterFatBinaryEnd(void **fatCubinHandle)
{
	LOG_DEBUG("\n");
}

void __cudaUnregisterFatBinary(void **fatCubinHandle)
{
	LOG_DEBUG("\n");
}

/**
 * - https://github.com/ROCm/rocm-systems.git
 *   void __hipRegisterFunction(hip::FatBinaryInfo** modules, const void* hostFunction,
 *                              char* deviceFunction, const char* deviceName, unsigned int threadLimit,
 *                              uint3* tid, uint3* bid, dim3* blockDim, dim3* gridDim, int* wSize);
 */
void __cudaRegisterFunction(void **fatCubinHandle, const char *hostFun,
			    char *deviceFun, const char *deviceName,
			    int thread_limit, uint3 *tid, uint3 *bid,
			    dim3 *bDim, dim3 *gDim, int *wSize)
{
	LOG_DEBUG("hostFun %p, deviceFun %p, deviceName %s, thread_limit %d\n",
		  hostFun, deviceFun, deviceName, thread_limit);
}

void __cudaRegisterVar(void **fatCubinHandle, char *hostVar,
		       char *deviceAddress, const char *deviceName,
		       int ext, size_t size, int constant, int global)
{
	LOG_DEBUG("hostVar %p, deviceAddress %p, deviceName %s, ext %d, size %ld, constant %d, global %d\n",
		  hostVar, deviceAddress, deviceName, ext, size, constant,
		  global);
}

void __cudaRegisterManagedVar(void **fatCubinHandle, void **hostVarPtrAddress,
			      char *deviceAddress, const char *deviceName,
			      int ext, size_t size, int constant, int global)
{
	LOG_DEBUG("hostVarPtrAddress %p, deviceAddress %p, deviceName %s, ext %d, size %ld, constant %d, global %d\n",
		  hostVarPtrAddress, deviceAddress, deviceName, ext, size,
		  constant, global);
}

unsigned __cudaPushCallConfiguration(dim3 gridDim, dim3 blockDim,
				     size_t sharedMem,
				     struct CUstream_st *stream)
{
	LOG_DEBUG("grid(%d,%d,%d), block(%d,%d,%d), sharedMem %ld\n",
		  gridDim.x, gridDim.y, gridDim.z,
		  blockDim.x, blockDim.y, blockDim.z,
		  sharedMem);
	return 0;
}

cudaError_t __cudaGetKernel(cudaKernel_t *kernel, const void *v)
{
	LOG_DEBUG("\n");
	return cudaSuccess;
}

cudaError_t __cudaPopCallConfiguration(dim3 *gridDim, dim3 *blockDim,
				       size_t *sharedMem, void *stream)
{
	LOG_DEBUG("\n");
	return cudaSuccess;
}

cudaError_t __cudaLaunchKernel(cudaKernel_t kernel, dim3 gridDim, dim3 blockDim,
			       void **args, size_t sharedMem,
			       cudaStream_t stream)
{
	LOG_DEBUG("kernel %p\n", kernel);
	return cudaSuccess;
}
#ifdef __cplusplus
}
#endif
