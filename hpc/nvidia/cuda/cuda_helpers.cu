// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include <string.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include <hcfft/hcfft.h>
#include <hcsparse/hcsparse.h>
#include "hpcc_helpers.h"
#include "cuda_adapter.h"
#else
#include <cuda.h>
#include <cuda_runtime.h>
#include <cufft.h>
#include <cusparse.h>
#include "cuda_helpers.h"
#endif


void gpu_init(int dev_id)
{
	int deviceId;

	cudaSetDevice(dev_id);
	gpu_check_gpu_error("Failed to initialize device!");
	cudaDeviceSetLimit(cudaLimitPrintfFifoSize, 1048576);

	cudaGetDevice(&deviceId);
	if (deviceId != dev_id) {
		fprintf(stderr, "Set device failed.\n");
		exit(1);
	}
}

int gpu_num(void)
{
	int count;
	cudaGetDeviceCount(&count);
	return count;
}

/*< check GPU errors >*/
void gpu_check_gpu_error(const char *msg)
{
	cudaError_t err = cudaGetLastError();
	if (cudaSuccess != err) {
		printf("CUDA error: %s: %s\n", msg, cudaGetErrorString(err));
		exit(1);
	}
}

const char *gpu_name(int dev_id, char *buf, int buf_len)
{
	cudaDeviceProp prop;
	CUDA_CHECK(cudaGetDeviceProperties(&prop, dev_id), return NULL);
	strncpy(buf, prop.name, buf_len);
	return buf;
}

int gpu_clock_rate(int dev_id)
{
#ifdef DEVPROP_HAVE_CLOCK_REATE
	cudaDeviceProp prop;
	CUDA_CHECK(cudaGetDeviceProperties(&prop, dev_id), return 0);
	return prop.clockRate;
#else
	int rate;
	CUDA_CHECK(cudaDeviceGetAttribute(&rate, cudaDevAttrClockRate, dev_id), return 0);
	return rate;
#endif
}

int gpu_max_threads_per_block(int dev_id)
{
	cudaDeviceProp prop;
	CUDA_CHECK(cudaGetDeviceProperties(&prop, dev_id), return 0);
	return prop.maxThreadsPerBlock;
}

const char *gpu_compute_cap_str(int major, int minor)
{
	switch (major) {
	case 10:
		return "Blackwell";
		break;
	case 9:
		return "Hopper";
		break;
	case 8:
		return "Ampere";
		break;
	case 7:
		return "Turing";
		break;
	case 6:
		return "Pascal";
		break;
	case 5:
		return "Maxwell";
		break;
	case 3:
		switch (minor) {
		case 0:	/* 3.0 */
			return "Kepler K10";
			break;
		case 5:	/* 3.5 */
			return "Kepler K20";
			break;
		}
		break;
	case 2:
		return "Tesla C2050";
		break;
	case 1:
		switch (minor) {
		case 0:	/* 1.0 */
			return "Tesla C870";
			break;
		case 3:	/* 3.3 */
			return "Tesla C1060";
			break;
		}
		break;
	}
	return "[Unknown]";
}

int cufft_version(int *_major, int *_minor, int *_patch)
{
	int major, minor, patch;

	CUFFT_CHECK(cufftGetProperty(MAJOR_VERSION, &major), return -1);
	CUFFT_CHECK(cufftGetProperty(MINOR_VERSION, &minor), return -1);
	CUFFT_CHECK(cufftGetProperty(PATCH_LEVEL, &patch), return -1);

	*_major = major;
	*_minor = minor;
	*_patch = patch;

	return 0;
}

int cusparse_version(int *_major, int *_minor, int *_patch)
{
	int major, minor, patch;

	cusparseGetProperty(MAJOR_VERSION, &major);
	cusparseGetProperty(MINOR_VERSION, &minor);
	cusparseGetProperty(PATCH_LEVEL, &patch);

	*_major = major;
	*_minor = minor;
	*_patch = patch;

	return 0;
}
