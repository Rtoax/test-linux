// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * Refs:
 * - https://github.com/ROCm/rocm-systems.git
 * - https://docs.nvidia.com/cuda/cuda-binary-utilities/index.html
 */
#include <elf.h>
#include "runtime.hpp"
#include "utils.hpp"
#include "fatbin.hpp"


static unsigned __hipFatMAGIC2 = 0x48495046;	// "HIPF"
static unsigned __cudaFatMAGIC2 = FATBINC_MAGIC;
static unsigned __hcFatMAGIC2 = 0x48504343;	// "HPCC"


/**
 * /usr/local/cuda-13.0/targets/x86_64-linux/include/driver_types.h
 * typedef __device_builtin__ struct CUkern_st *cudaKernel_t;
 */
struct CUkern_st {
};


/**
 * - https://github.com/ROCm/rocm-systems.git
 *   void** __hipRegisterFatBinary(const void* data);
 */
void **__cudaRegisterFatBinary(void *fatCubin)
{
	struct __CudaFatBinaryWrapper *wrapper;

	wrapper = (struct __CudaFatBinaryWrapper *)fatCubin;

	for (;;) {
		/* Check magic */
		if ((wrapper->magic != __cudaFatMAGIC2 &&
		     wrapper->magic != __hipFatMAGIC2 &&
		     wrapper->magic != __hcFatMAGIC2) ||
		    wrapper->version != FATBINC_VERSION) {
			DEBUG_WARN("Cannot Register fat binary. FatMagic: %u version: %u\n",
				   wrapper->magic, wrapper->version);
			break;
		}

		DEBUG_DBG("fatCubin %p, magic 0x%x(%c%c%c%c), version %d, fatbin %p\n",
			  fatCubin, wrapper->magic,
			  (wrapper->magic >> 24) & 0xff,
			  (wrapper->magic >> 16) & 0xff,
			  (wrapper->magic >> 8) & 0xff,
			  wrapper->magic & 0xff,
			  wrapper->version, wrapper->fatbin,
			  wrapper->dummy1);

		debug_memdump(wrapper, sizeof(struct __CudaFatBinaryWrapper));

		fakeCudaFatbinParser((struct fatBinaryHeader *)wrapper->fatbin);

		/* For next */
		wrapper++;
	}

	return NULL;
}

void __cudaRegisterFatBinaryEnd(void **fatCubinHandle)
{
	DEBUG_DBG("\n");
}

void __cudaUnregisterFatBinary(void **fatCubinHandle)
{
	DEBUG_DBG("\n");
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
	DEBUG_DBG("hostFun %p, deviceFun %p, deviceName %s, thread_limit %d\n",
		  hostFun, deviceFun, deviceName, thread_limit);
}

void __cudaRegisterVar(void **fatCubinHandle, char *hostVar,
		       char *deviceAddress, const char *deviceName,
		       int ext, size_t size, int constant, int global)
{
	DEBUG_DBG("hostVar %p, deviceAddress %p, deviceName %s, ext %d, size %ld, constant %d, global %d\n",
		  hostVar, deviceAddress, deviceName, ext, size, constant,
		  global);
}

/**
 * void __hipRegisterManagedVar(void* hipModule, void** pointer, void* init_value,
 *                              const char* name, size_t size, unsigned align);
 */
#ifdef HAVE_HPCC
hcError_t __hcRegisterManagedVar(void *fatCubinHandle, void **hostVarPtrAddress,
				 void *deviceAddress, const char *deviceName,
				 size_t size, unsigned int align)
{
	DEBUG_DBG("\n");
	return hcSuccess;
}
#else
void __cudaRegisterManagedVar(void **fatCubinHandle, void **hostVarPtrAddress,
			      char *deviceAddress, const char *deviceName,
			      int ext, size_t size, int constant, int global)
{
	DEBUG_DBG("hostVarPtrAddress %p, deviceAddress %p, deviceName %s, ext %d, size %ld, constant %d, global %d\n",
		  hostVarPtrAddress, deviceAddress, deviceName, ext, size,
		  constant, global);
}
#endif

unsigned __cudaPushCallConfiguration(dim3 gridDim, dim3 blockDim,
				     size_t sharedMem,
				     struct CUstream_st *stream)
{
	DEBUG_DBG("grid(%d,%d,%d), block(%d,%d,%d), sharedMem %ld\n",
		  gridDim.x, gridDim.y, gridDim.z,
		  blockDim.x, blockDim.y, blockDim.z,
		  sharedMem);
	return 0;
}

cudaError_t __cudaGetKernel(cudaKernel_t *kernel, const void *v)
{
	DEBUG_DBG("kernel %p, v %p\n", kernel, v);
	return cudaSuccess;
}

cudaError_t __cudaPopCallConfiguration(dim3 *gridDim, dim3 *blockDim,
				       size_t *sharedMem, void *stream)
{
	DEBUG_DBG("\n");
	return cudaSuccess;
}

cudaError_t __cudaLaunchKernel(cudaKernel_t kernel, dim3 gridDim, dim3 blockDim,
			       void **args, size_t sharedMem,
			       cudaStream_t stream)
{
	DEBUG_DBG("kernel %p\n", kernel);
	return cudaSuccess;
}
