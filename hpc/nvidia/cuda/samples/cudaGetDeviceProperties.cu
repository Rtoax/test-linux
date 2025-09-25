// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * - NVIDIA H800
 *   commit 37abe51dfb76 ("hpc: DeviceProp: NVIDIA H800 v2")
 *
 * - NVIDIA GeForce RTX 3060
 *   commit 3dfdd4a370f2 ("hpc: DeviceProp: NVIDIA GeForce RTX 3060")
 *
 * - MetaX Mars 03
 *   commit 79e92d93846f ("hpc: DeviceProp: MetaX Mars X203")
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
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include "hpcc_helpers.h"
#include "cuda_adapter.h"
#elif defined(HAVE_HIP)
# define __USE_HIP__	1
#include <hip/hip_runtime.h>
#include "cuda_helpers.h"
#include "cuda_adapter.h"
#else
#include <cuda.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#endif

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
	int i, dev_id, dev_count;
	cudaDeviceProp prop;

	dev_id = 0;

	fprintf(stderr, "Usage: %s [dev_id=<N>]\n", argv[0]);

	for (i = 1; i < argc; i++) {
#define arg_eq(v) if (!strncmp(#v"=", argv[i], strlen(#v) + 1)) \
			v = atoi(argv[i] + strlen(#v) + 1);
		arg_eq(dev_id);
#undef arg_eq
	}

	gpu_init(dev_id);

	dev_count = gpu_num();

	cudaGetDeviceProperties(&prop, dev_id);

#define PRINT_d(v)	printf("%s %d\n", #v, prop.v);
#define PRINT_zu(v)	printf("%s %zu\n", #v, prop.v);
#define PRINT_ld(v)	printf("%s %ld\n", #v, prop.v);

	printf("name %s, running on device %d, total %d\n", prop.name, dev_id, dev_count);
	/* uuid is 16-byte unique identifier */
	printuuid("uuid", (void *)&prop.uuid, 16);
	/* luid 8-byte locally unique identifier */
	printuuid("luid", (void *)&prop.luid, 8);

	/* Information about memory */
	printf("totalGlobalMem %ld (%.0lf GiB)\n", prop.totalGlobalMem, prop.totalGlobalMem / 1e9);
	printf("totalConstMem %ld (%.0lf GiB)\n", prop.totalConstMem, prop.totalConstMem / 1e9);
	printf("l2CacheSize %d B (%d MB)\n", prop.l2CacheSize, prop.l2CacheSize / 1024 / 1024);
	PRINT_d(globalL1CacheSupported);
	PRINT_d(localL1CacheSupported);
	PRINT_d(managedMemory);
	PRINT_d(memoryBusWidth);
	PRINT_ld(sharedMemPerBlock);
	PRINT_ld(memPitch);
	/**
	 * see also $ nvidia-smi -q -d ECC
	 * - commit 120e7c6f3062 ("cudaGetDeviceProperties: ECC info")
	 */
	PRINT_d(ECCEnabled);

	PRINT_ld(textureAlignment);
	PRINT_ld(texturePitchAlignment);

	PRINT_d(regsPerBlock);
	PRINT_d(deviceOverlap);

	/* Information about Core/Thread */
	PRINT_d(multiProcessorCount);
	PRINT_d(maxThreadsPerMultiProcessor);
	printf("Theoretical number of concurrent hardware threads: %d\n",
		prop.multiProcessorCount * prop.maxThreadsPerMultiProcessor);

	printf("maxThreadsPerBlock %d >= blockDim.x * blockDim.y * blockDim.z\n",
		prop.maxThreadsPerBlock);

	for (i = 0; i < 3; i++)
		printf("maxThreadsDim[%d] = %-8d >= blockDim.%s\n", i,
			prop.maxThreadsDim[i], "x\0y\0z\0" + (2 * i));

	for (i = 0; i < 3; i++)
		printf("maxGridSize[%d] = %-16d >= gridDim.%s\n", i,
			prop.maxGridSize[i], "x\0y\0z\0" + (2 * i));

	/* Information about device */
	{
		CUdevice cuDevice;
		cuDeviceGet(&cuDevice, dev_id);
		int major, minor;
		cuDeviceComputeCapability(&major, &minor, cuDevice);
		printf("Compute Capability: major.minor %d.%d %s\n", major, minor,
			gpu_compute_cap_str(major, minor));
	}

	printf("Compute Capability: major.minor %d.%d, %s\n", prop.major, prop.minor,
		gpu_compute_cap_str(prop.major, prop.minor));

#if !defined(__CUDACC__)
	PRINT_d(kernelExecTimeoutEnabled);
#endif
	PRINT_d(integrated);

#ifdef DEVPROP_HAVE_CLOCK_REATE
	printf("clockRate %d Hz\n", prop.clockRate);
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
