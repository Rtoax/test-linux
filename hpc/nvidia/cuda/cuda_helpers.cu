// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025 Rong Tao */
#include <stdio.h>
#include <string.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


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

/**
 * https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html
 * https://www.nvidia.com/en-us/data-center/technologies/blackwell-architecture/
 * https://www.nvidia.com/en-us/data-center/technologies/hopper-architecture/
 * https://www.nvidia.com/en-us/data-center/ampere-architecture/
 */
const char *gpu_compute_cap_str(int major, int minor)
{
	switch (major) {
	case 12:
		switch (minor) {
		case 1:
			/**
			 * FIXME: just give 12.1 to NVIDIA GDX Spark
			 */
			return "GB10 Grace Blackwell";
			break;
		default:
			break;
		}
		break;
	/* Year 2024 */
	case 10:
		return "Blackwell";
		break;
	/* Year 2022 */
	case 9:
		return "Hopper";
		break;
	/* Year 2020 */
	case 8:
		switch (minor) {
		case 0:
		case 6:
		case 7:
			return "Ampere A100";
			break;
		/* Year 2022 */
		case 9:
			return "Ada Lovelace";
			break;
		default:
			return "Ampere";
		}
		break;
	/* Year 2017 */
	case 7:
		switch (minor) {
		case 0:
			return "Volta V100";
			break;
		case 5:
			return "Turing";
			break;
		default:
			return "Volta/Turing";
			break;
		}
		break;
	/* Year 2016 */
	case 6:
		switch (minor) {
		case 0:
			return "Pascal P100";
			break;
		default:
			return "Pascal";
			break;
		}
		break;
	/* Year 2014 */
	case 5:
		return "Maxwell";
		break;
	/* Year 2012 */
	case 3:
		switch (minor) {
		case 0:
			return "Kepler K10";
			break;
		case 5:
			return "Kepler K20";
			break;
		default:
			return "Kepler";
			break;
		}
		break;
	/* Year 2010 */
	case 2:
		switch (minor) {
		case 0:
			return "Fermi GeForce 400/Quadro 600";
			break;
		case 1:
			return "Fermi GeForce 500/Quadro 600";
			break;
		default:
			return "Fermi";
			break;
		}
		break;
	case 1:
		switch (minor) {
		case 0:
			return "Tesla C870";
			break;
		case 3:
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

#ifdef HAVE_HIP
#define MAJOR_VERSION   HIPFFT_MAJOR_VERSION
#define MINOR_VERSION   HIPFFT_MINOR_VERSION
#define PATCH_LEVEL     HIPFFT_PATCH_LEVEL
#endif
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

#ifndef HAVE_HIP
	cusparseGetProperty(MAJOR_VERSION, &major);
	cusparseGetProperty(MINOR_VERSION, &minor);
	cusparseGetProperty(PATCH_LEVEL, &patch);

	*_major = major;
	*_minor = minor;
	*_patch = patch;
#else
	/**
	 * HIP has no hipsparseGetProperty()
	 * ubuntu25.04 libhipsparse-dev = 5.7.1-1build1
	 * fedora42 hipsparse-6.3.0-4.fc42.x86_64
	 */
	*_major = 6;
	*_minor = 3;
	*_patch = 0;
#endif

	return 0;
}
