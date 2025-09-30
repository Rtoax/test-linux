// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * - NVIDIA H800
 *   commit 4aa4dfa57336 ("hpc: DeviceProp: Nvidia H800 v3")
 *
 * - NVIDIA GeForce RTX 3060
 *   commit 3dfdd4a370f2 ("hpc: DeviceProp: NVIDIA GeForce RTX 3060")
 *
 * - MetaX Mars 03
 *   commit 0fba063e1fae ("hpc: DeviceProp: Metax Mars X203")
 *
 * - cuda-12.9 struct cudaDeviceProp
 *   commit d072d32dcb00 ("cuda: cudaGetDeviceProperties.cu: display more")
 *
 * Links
 * - https://docs.nvidia.com/cuda/cuda-runtime-api/structcudaDeviceProp.html
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


void printuuid(const char *pfx, void *uuid, size_t size)
{
	uint8_t *u8 = (uint8_t *)uuid;
	printf("%s ", pfx);
	for (size_t i = 0; i < size; i++) {
		uint8_t c = u8[i];
		printf("%02x%c", c, i == (size - 1) ? '\n' : ' ');
	}
}

int main(int argc, char *argv[])
{
	int i, dev, dev_count;
	cudaDeviceProp prop;

	dev = 0;

	fprintf(stderr, "Usage: %s [dev=<N>]\n", argv[0]);

	for (i = 1; i < argc; i++) {
#define arg_eq(v) if (!strncmp(#v"=", argv[i], strlen(#v) + 1)) \
			v = atoi(argv[i] + strlen(#v) + 1);
		arg_eq(dev);
#undef arg_eq
	}

	gpu_init(dev);

	dev_count = gpu_num();

	cudaGetDeviceProperties(&prop, dev);

#define PRINT_s(v)	printf("%s %s\n", #v, prop.v);
#define PRINT_d(v)	printf("%s %d\n", #v, prop.v);
#define PRINT_zu(v)	printf("%s %zu\n", #v, prop.v);
#define PRINT_ld(v)	printf("%s %ld\n", #v, prop.v);

	printf("name %s, running on device %d, total %d\n", prop.name, dev, dev_count);
	/* uuid is 16-byte unique identifier */
	printuuid("uuid", (void *)&prop.uuid, 16);
	/* luid 8-byte locally unique identifier */
	printuuid("luid", (void *)&prop.luid, 8);

	PRINT_d(isMultiGpuBoard);
	PRINT_d(multiGpuBoardGroupID);
	PRINT_d(pciBusID);
	PRINT_d(pciDeviceID);
	PRINT_d(pciDomainID);
#if !defined(__CUDACC__)
	/* 1: if it is a large PCI bar device, else 0 */
	PRINT_d(isLargeBar);
#endif
	PRINT_d(tccDriver);
	PRINT_d(asyncEngineCount);
	PRINT_d(unifiedAddressing);

	/* Information about memory */
	PRINT_d(pageableMemoryAccess);
	PRINT_d(pageableMemoryAccessUsesHostPageTables);
	printf("totalGlobalMem %ld (%.0lf GiB)\n", prop.totalGlobalMem, prop.totalGlobalMem / 1e9);
	printf("totalConstMem %ld (%.0lf GiB)\n", prop.totalConstMem, prop.totalConstMem / 1e9);
	printf("l2CacheSize %d B (%d MB)\n", prop.l2CacheSize, prop.l2CacheSize / 1024 / 1024);
#if defined(__HPCC__)
	PRINT_d(l2CacheLineSize);
#endif
	PRINT_d(persistingL2CacheMaxSize);
	PRINT_d(globalL1CacheSupported);
	PRINT_d(localL1CacheSupported);
	PRINT_d(managedMemory);
	PRINT_d(memoryBusWidth);
#if !defined(__CUDACC__)
	PRINT_d(memoryClockRate);
#endif
	PRINT_ld(sharedMemPerBlock);
	PRINT_ld(sharedMemPerMultiprocessor);
	PRINT_ld(sharedMemPerBlockOptin);
	PRINT_ld(reservedSharedMemPerBlock);
#if !defined(__CUDACC__)
	PRINT_ld(maxSharedMemoryPerMultiProcessor);
	PRINT_d(computeMode);
#endif
	PRINT_ld(memPitch);
	PRINT_d(canMapHostMemory);
	PRINT_d(canUseHostPointerForRegisteredMem);
	PRINT_d(directManagedMemAccessFromHost);
	PRINT_d(maxBlocksPerMultiProcessor);
	PRINT_d(accessPolicyMaxWindowSize);
#if defined(__HPCC__)
	PRINT_ld(stackMemPerThread);
	PRINT_d(mqlBarrierValue);
	PRINT_d(virtualMemoryManagement);
	PRINT_d(localSocketId);
#endif

	/**
	 * see also $ nvidia-smi -q -d ECC
	 * - commit ee378b727aaf ("nvidia: h800: ECC info")
	 * - commit 120e7c6f3062 ("cudaGetDeviceProperties: ECC info")
	 */
	PRINT_d(ECCEnabled);

	PRINT_ld(textureAlignment);
	PRINT_ld(texturePitchAlignment);
	PRINT_d(maxTexture1D);
	PRINT_d(maxTexture1DMipmap);
#if !defined(__CUDACC__)
	PRINT_d(maxTexture1DLinear);
#endif
	PRINT_d(maxTexture2D[0]);
	PRINT_d(maxTexture2D[1]);
	PRINT_d(maxTexture2DMipmap[0]);
	PRINT_d(maxTexture2DMipmap[1]);
	PRINT_d(maxTexture2DLinear[0]);
	PRINT_d(maxTexture2DLinear[1]);
	PRINT_d(maxTexture2DLinear[2]);
	PRINT_d(maxTexture2DGather[0]);
	PRINT_d(maxTexture2DGather[1]);
	PRINT_d(maxTexture3D[0]);
	PRINT_d(maxTexture3D[1]);
	PRINT_d(maxTexture3D[2]);
	PRINT_d(maxTexture3DAlt[0]);
	PRINT_d(maxTexture3DAlt[1]);
	PRINT_d(maxTexture3DAlt[2]);
	PRINT_d(maxTextureCubemap);
	PRINT_d(maxTexture1DLayered[0]);
	PRINT_d(maxTexture1DLayered[1]);
	PRINT_d(maxTexture2DLayered[0]);
	PRINT_d(maxTexture2DLayered[1]);
	PRINT_d(maxTexture2DLayered[2]);
	PRINT_d(maxTextureCubemapLayered[0]);
	PRINT_d(maxTextureCubemapLayered[1]);

	PRINT_d(maxSurface1D);
	PRINT_d(maxSurface2D[0]);
	PRINT_d(maxSurface2D[1]);
	PRINT_d(maxSurface3D[0]);
	PRINT_d(maxSurface3D[1]);
	PRINT_d(maxSurface3D[2]);
	PRINT_d(maxSurface1DLayered[0]);
	PRINT_d(maxSurface1DLayered[1]);
	PRINT_d(maxSurface2DLayered[0]);
	PRINT_d(maxSurface2DLayered[1]);
	PRINT_d(maxSurfaceCubemap);
	PRINT_d(maxSurfaceCubemapLayered[0]);
	PRINT_d(maxSurfaceCubemapLayered[1]);
	PRINT_ld(surfaceAlignment);

	/* Device can possibly execute multiple kernels concurrently */
	PRINT_d(concurrentKernels);
	PRINT_d(concurrentManagedAccess);
	PRINT_d(cooperativeLaunch);
#if !defined(__CUDACC__)
	PRINT_d(cooperativeMultiDeviceLaunch);
	PRINT_d(cooperativeMultiDeviceUnmatchedFunc);
	PRINT_d(cooperativeMultiDeviceUnmatchedGridDim);
	PRINT_d(cooperativeMultiDeviceUnmatchedBlockDim);
	PRINT_d(cooperativeMultiDeviceUnmatchedSharedMem);
#endif

	PRINT_d(streamPrioritiesSupported);

	PRINT_d(regsPerBlock);
	PRINT_d(regsPerMultiprocessor);
#if !defined(__CUDACC__)
	PRINT_d(deviceOverlap);
	PRINT_d(singleToDoublePrecisionPerfRatio);
#endif
	PRINT_d(hostNativeAtomicSupported);
	PRINT_d(computePreemptionSupported);

	/* Information about Core/Thread */
	PRINT_d(multiProcessorCount);
	PRINT_d(maxThreadsPerMultiProcessor);
	printf("Theoretical number of concurrent hardware threads: %d\n",
		prop.multiProcessorCount * prop.maxThreadsPerMultiProcessor);

	printf("maxThreadsPerBlock %d >= blockDim.x * blockDim.y * blockDim.z\n",
		prop.maxThreadsPerBlock);

	char dim_s[] = "x\0y\0z\0";

	for (i = 0; i < 3; i++)
		printf("maxThreadsDim[%d] = %-8d >= blockDim.%s\n", i,
			prop.maxThreadsDim[i], dim_s + 2 * i);

	for (i = 0; i < 3; i++)
		printf("maxGridSize[%d] = %-16d >= gridDim.%s\n", i,
			prop.maxGridSize[i], dim_s + 2 * i);

	/* Information about device */
	{
		CUdevice cuDevice;
		cuDeviceGet(&cuDevice, dev);
		int major, minor;
		cuDeviceComputeCapability(&major, &minor, cuDevice);
		printf("Compute Capability: major.minor %d.%d %s\n", major, minor,
			gpu_compute_cap_str(major, minor));
	}

	printf("Compute Capability: major.minor %d.%d, %s\n", prop.major, prop.minor,
		gpu_compute_cap_str(prop.major, prop.minor));
#if defined(__HPCC__)
	PRINT_d(step);
#endif
#if !defined(__CUDACC__)
	PRINT_d(asicRevision);
#endif
#ifdef __HIPCC__
	PRINT_s(gcnArchName);
#elif defined(__HPCC__)
	PRINT_s(htArchName);
#endif

#if !defined(__CUDACC__)
	PRINT_d(kernelExecTimeoutEnabled);
#endif
	PRINT_d(integrated);

#ifdef DEVPROP_HAVE_CLOCK_REATE
	printf("clockRate %d Hz\n", prop.clockRate);
#endif

#if !defined(__CUDACC__)
	PRINT_d(clockInstructionRate);
#endif

	/**
	 * Threads are batched in groups that we’ll call Wavefronts or waves
	 * (or warps in Nvidia lingo). Like the name, the numbers of threads
	 * in a wave is architecture dependent, 32 on NVIDIA GPUs, 64 on AMD’s
	 * GCN and variable on Intel cards.
	 * https://flashypixels.wordpress.com/2018/11/10/intro-to-gpu-scalarization-part-1/
	 *
	 * MetaX wave/warp size is 64.
	 */
	PRINT_d(warpSize);
#if !defined(__CUDACC__) && !defined(__HIPCC__)
	PRINT_d(waveSize);
#endif

	return 0;
}
