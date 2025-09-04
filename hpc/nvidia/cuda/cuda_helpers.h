// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#pragma once

#ifndef likely
#define likely(x)    __builtin_expect(!!(x), 1)
#endif
#ifndef unlikely
#define unlikely(x)  __builtin_expect(!!(x), 0)
#endif

#define CUDA_CHECK(CALL, ERROR_DO)	{				\
	cudaError_t __err = CALL;					\
	if (unlikely(__err != cudaSuccess)) {				\
		fprintf(stderr, "\033[31m");				\
		fprintf(stderr, "ERROR: %s:%d Call %s failed, %s\n",	\
			__func__, __LINE__,				\
			#CALL, cudaGetErrorString(__err));		\
		fprintf(stderr, "\033[m");				\
		ERROR_DO;						\
	}								\
}
#define CUDA_CHECK_EXIT(CALL) CUDA_CHECK(CALL, exit(-1))

#define CUBLAS_CHECK(CALL, ERROR_DO)	{				\
	cublasStatus_t __status = CALL;					\
	if (unlikely(__status != CUBLAS_STATUS_SUCCESS)) {		\
		fprintf(stderr, "\033[31m");				\
		fprintf(stderr, "ERROR: %s:%d Blas %s failed, %s\n",	\
			__func__, __LINE__,				\
			#CALL, cublasGetStatusString(__status));	\
		fprintf(stderr, "\033[m");				\
		ERROR_DO;						\
	}								\
}
#define CUBLAS_CHECK_EXIT(CALL) CUBLAS_CHECK(CALL, exit(-1))

#define CURAND_CHECK(CALL, ERROR_DO)	{				\
	curandStatus_t __status = CALL;					\
	if (unlikely(__status != CURAND_STATUS_SUCCESS)) {		\
		fprintf(stderr, "\033[31m");				\
		fprintf(stderr, "ERROR: %s:%d Rand %s failed, %d\n",	\
			__func__, __LINE__,				\
			#CALL, __status);				\
		fprintf(stderr, "\033[m");				\
		ERROR_DO;						\
	}								\
}

#define CUFFT_CHECK(CALL, ERROR_DO)	{				\
	cufftResult __status = CALL;					\
	if (unlikely(__status != CUFFT_SUCCESS)) {			\
		fprintf(stderr, "\033[31m");				\
		fprintf(stderr, "ERROR: %s:%d Rand %s failed, %d\n",	\
			__func__, __LINE__,				\
			#CALL, __status);				\
		fprintf(stderr, "\033[m");				\
		ERROR_DO;						\
	}								\
}

#ifdef CUDA_VERSION_MAJOR
# if CUDA_VERSION_MAJOR < 13
#  define DEVPROP_HAVE_CLOCK_REATE	1
# endif
#else
# define DEVPROP_HAVE_CLOCK_REATE	1
#endif


void gpu_init(int dev_id);
void gpu_check_gpu_error(const char *msg);

int gpu_num(void);
const char *gpu_name(int dev_id, char *buf, int buf_len);
int gpu_clock_rate(int dev_id);
int gpu_max_threads_per_block(int dev_id);
const char *gpu_compute_cap_str(int major, int minor);

int cufft_version(int *_major, int *_minor, int *_patch);
