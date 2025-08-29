// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * BLAS (Basic Linear Algebra Subprograms)
 *
 * refs:
 * - https://docs.nvidia.com/cuda/cublas/index.html
 */
#include <assert.h>
#include <argp.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include <time.h>
#if defined(HAVE_HCCL)
# include <hc_runtime.h>
# include <hcblas/hcblas.h>
# include <hcblas/hcblasLt.h>
# include "hpcc_helpers.h"
# include "cuda2hccl.h"
# define NAME	"MetaX BLAS"
#else
# include <cuda_runtime.h>
# include <cublas_v2.h>
# include <cublasLt.h>
# include "cuda_helpers.h"
# define NAME	"CUDA BLAS"
#endif

#define IDX2C(i, j, ld)	(((j) * (ld)) + (i))
#define ARRAY_SIZE(arr)	(sizeof(arr) / sizeof(arr[0]))

enum test_type {
	TEST_SCAL_FP32,
	TEST_SCAL_FP64,
	TEST_AXPY_FP32,
	TEST_AXPY_FP64,
	TEST_COPY_FP32,
	TEST_COPY_FP64,
	TEST_DOT_FP32,
	TEST_DOT_FP64,
	TEST_NRM2_FP32,
	TEST_NRM2_FP64,
#if 0
	TEST_ROT,	/* TODO */
	TEST_ROTG,	/* TODO */
	TEST_ROTM,	/* TODO */
#endif
	/**
	 * GEMM: General Matrix-Matrix Multiplication
	 *
	 * - commit a9912e59ae2e ("hpc: blas: gemm: Cmp MetaX Mars X203 and Nvidia H800")
	 * - commit 68f09e1a28c3 ("hpc: blas: gemm: Test NVIDIA GeForce RTX 3060 fp16/fp32/fp64")
	 */
	TEST_GEMM_FP16,
	TEST_GEMM_FP32,
	TEST_GEMM_FP64,
	/**
	 * - commit de0a14c3e683 ("hpc: blas: gemmex: Test NVIDIA GeForce RTX 3060 fp16/fp32/fp64")
	 */
	TEST_GEMMEX_FP16,
	TEST_GEMMEX_FP32,
	TEST_GEMMEX_FP64,
	TEST_GEMMEX_INT8,
	/**
	 * Matrix Multiplication
	 *
	 * - commit 3237eede2fb2 ("hpc: blas: matmul: Test MetaX Mars X203 fp16/fp32/fp64")
	 * - commit 54df2b69c4cc ("hpc: blas: matmul: Test NVIDIA GeForce RTX 3060 fp16/fp32/fp64")
	 */
	TEST_MATMUL_FP16,
	TEST_MATMUL_FP32,
	TEST_MATMUL_FP64,
	/**
	 * NOTE: Matmul int8 is faster than GemmEx int8
	 * - commit f1389d15082c ("hpc: blas: int8: MetaX Mars X203: Matmul faster than GemmEx")
	 */
	TEST_MATMUL_INT8,
	/* Test different dataType of blasLtMatmul() */
	TEST_MATMUL_INT8_2,
	TEST_MAX,
	TEST_ALL = TEST_MAX,
#define TEST_LIST_STR	"scal-fp32|scal-fp64|" \
			"axpy-fp32|axpy-fp64|" \
			"copy-fp32|copy-fp64|" \
			"dot-fp32|dot-fp64|" \
			"nrm2-fp32|nrm2-fp64|" \
			"gemm-fp16|gemm-fp32|gemm-fp64|" \
			"gemmex-fp16|gemmex-fp32|gemmex-fp64|" \
			"gemmex-int8|" \
			"matmul-int8|matmul-int8-2|" \
			"matmul-fp16|matmul-fp32|matmul-fp64"
};

struct {
	int gpu;
	/**
	 * Use m, n first, then, use k (see cublasSgemm()). and m used as rows,
	 * n used as columns.
	 */
	unsigned long m, n, k;
	int alpha, beta;
	unsigned long nloop;
	enum test_type test_type;
	bool set_value;
	unsigned int value;
	bool verbose;
	char *output_file_suffix;
} env = {
	.gpu = 0,
	.m = 6,
	.n = 5,
	.k = 1,
	.alpha = 2,
	.beta = 2,
	.nloop = 1,
	.test_type = TEST_ALL,
	.set_value = false,
	.value = 0,
	.verbose = false,
	.output_file_suffix = NULL,
};

struct test;

struct test_operations {
	/* operations */
	int (*create_blas)(struct test *test);
	int (*prepare_data)(struct test *test);
	int (*run_blas)(struct test *test);
	double (*get_flops)(struct test *test);
	int (*display_data)(struct test *test);
	int (*free_data)(struct test *test);
	int (*destroy_blas)(struct test *test);
};

struct test {
	const char *name;
	enum test_type type;

	cublasHandle_t handle;

	/**
	 * BLASLt - The cuBLASLt library is a new lightweight library dedicated
	 * to GEneral Matrix-to-matrix Multiply (GEMM) operations with a new
	 * flexible API.
	 */
	struct {
		cublasLtHandle_t ltHandle;
		cublasLtMatmulDesc_t matmulDesc;
		cublasLtMatrixLayout_t layoutA, layoutB, layoutC;
		cublasLtMatmulPreference_t pref;
		cublasLtMatmulHeuristicResult_t heuristic_result;
		void *workspace;
		size_t workspaceSize;
	};
#define Z0	{NULL,NULL,NULL,NULL,NULL,NULL,{},NULL,1<<22/*4MB*/}

	union {
		int8_t *int8;
		int32_t *int32;
		half *fp16;
		float *fp32;
		double *fp64;
		void *ptr;
	} host_A, host_B, host_C, dev_A, dev_B, dev_C;
#define Z1      {NULL}

	union {
		int8_t int8;
		int32_t int32;
		half fp16;
		float fp32;
		double fp64;
	} result;
#define Z2      {0}

	struct {
		unsigned long start, end;
	} create, prepare, display, free, destroy;
#define Z3      {0,0}
	struct {
		cudaEvent_t start, end;
		float elapsed; /* ms */
		double flops;
	} run;
#define Z4      {NULL,NULL,0.0,0.0}
	struct {
		FILE *fp;
		char *file;
	} output;
#define Z5	{NULL,NULL}
#define ZERO_TEST(name, type) name,type,NULL,Z0,Z1,Z1,Z1,Z1,Z1,Z1,Z2,Z3,Z3,Z3,Z3,Z3,Z4,Z5
	struct test_operations ops;
};

const char *version = "v0.0.7 (" NAME ")";

const char argp_prog_doc[] =
	"USAGE: [-g <GPU>] [-v] [=t=<TYPE>]\n"
	"\n"
	"Examples:\n"
	" $ time ./blas -m10 -n10\n"
	" $ time ./blas -t scal-fp32\n"
	"\n"
	"TYPE: " TEST_LIST_STR "\n";

static const struct argp_option opts[] = {
	{ "gpu", 'g', "GPU", 0, "Running on GPU" },
	{ NULL, 'm', "M", 0, "M number" },
	{ NULL, 'n', "N", 0, "N number" },
	{ NULL, 'k', "K", 0, "K number" },
	{ "alpha", 'A', "ALPHA", 0, "Set alpha value" },
	{ "beta", 'B', "BETA", 0, "Set beta value" },
	{ "type", 't', "TYPE", 0, "set test type, see TYPE " },
	{ "init-val", 'i', "INIT_VAL", 0, "Set matrix values" },
	{ "nloop", 'N', "NLOOP", 0, "Test loop number" },
	{ "verbose", 'v', NULL, 1, "Display detail" },
	{ "version", 'V', NULL, 1, "Display version" },
	{ "output-file-suffix", 'O', "FILE", 0, "Specify output file suffix, prefix is test name" },
	{},
};

static void print_blas_version(void)
{
	int major, minor, patch;
	cublasGetProperty(MAJOR_VERSION, &major);
	cublasGetProperty(MINOR_VERSION, &minor);
	cublasGetProperty(PATCH_LEVEL, &patch);
	printf("%s %d.%d.%d\n", NAME, major, minor, patch);
}

static void print_version(void)
{
	print_blas_version();
	printf("test %s\n", version);
}

static inline unsigned long nsecs(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000000000UL + ts.tv_nsec;
}

int fwrite_test(struct test *test, void *host_ptr, size_t size, size_t nmemb)
{
	size_t n;
	if (!test->output.fp)
		return -EINVAL;
	if (env.verbose)
		fprintf(stderr, "Write to %s\n", test->output.file);
	n = fwrite(host_ptr, size, nmemb, test->output.fp);
	fflush(test->output.fp);
	return n;
}

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'g':
		env.gpu = strtoul(arg, NULL, 10);
		break;
	case 'm':
		env.m = strtoul(arg, NULL, 10);
		break;
	case 'n':
		env.n = strtoul(arg, NULL, 10);
		break;
	case 'k':
		env.k = strtoul(arg, NULL, 10);
		break;
	case 'A':
		env.alpha = strtoul(arg, NULL, 10);
		break;
	case 'B':
		env.beta = strtoul(arg, NULL, 10);
		break;
	case 't':
		if (!strcmp(arg, "scal-fp32"))
			env.test_type = TEST_SCAL_FP32;
		else if (!strcmp(arg, "scal-fp64"))
			env.test_type = TEST_SCAL_FP64;
		else if (!strcmp(arg, "axpy-fp32"))
			env.test_type = TEST_AXPY_FP32;
		else if (!strcmp(arg, "axpy-fp64"))
			env.test_type = TEST_AXPY_FP64;
		else if (!strcmp(arg, "copy-fp32"))
			env.test_type = TEST_COPY_FP32;
		else if (!strcmp(arg, "copy-fp64"))
			env.test_type = TEST_COPY_FP64;
		else if (!strcmp(arg, "dot-fp32"))
			env.test_type = TEST_DOT_FP32;
		else if (!strcmp(arg, "dot-fp64"))
			env.test_type = TEST_DOT_FP64;
		else if (!strcmp(arg, "nrm2-fp32"))
			env.test_type = TEST_NRM2_FP32;
		else if (!strcmp(arg, "nrm2-fp64"))
			env.test_type = TEST_NRM2_FP64;
		else if (!strcmp(arg, "gemm-fp16"))
			env.test_type = TEST_GEMM_FP16;
		else if (!strcmp(arg, "gemm-fp32"))
			env.test_type = TEST_GEMM_FP32;
		else if (!strcmp(arg, "gemm-fp64"))
			env.test_type = TEST_GEMM_FP64;
		else if (!strcmp(arg, "gemmex-fp16"))
			env.test_type = TEST_GEMMEX_FP16;
		else if (!strcmp(arg, "gemmex-fp32"))
			env.test_type = TEST_GEMMEX_FP32;
		else if (!strcmp(arg, "gemmex-fp64"))
			env.test_type = TEST_GEMMEX_FP64;
		else if (!strcmp(arg, "gemmex-int8"))
			env.test_type = TEST_GEMMEX_INT8;
		else if (!strcmp(arg, "matmul-fp16"))
			env.test_type = TEST_MATMUL_FP16;
		else if (!strcmp(arg, "matmul-fp32"))
			env.test_type = TEST_MATMUL_FP32;
		else if (!strcmp(arg, "matmul-fp64"))
			env.test_type = TEST_MATMUL_FP64;
		else if (!strcmp(arg, "matmul-int8"))
			env.test_type = TEST_MATMUL_INT8;
		else if (!strcmp(arg, "matmul-int8-2"))
			env.test_type = TEST_MATMUL_INT8_2;
		else {
			fprintf(stderr, "Support TEST TYPE: " TEST_LIST_STR "\n");
			exit(-EINVAL);
		}
		break;
	case 'i':
		env.set_value = true;
		env.value = atoi(arg);
		break;
	case 'N':
		env.nloop = strtoul(arg, NULL, 10);
		break;
	case 'v':
		env.verbose = true;
		break;
	case 'V':
		print_version();
		exit(EXIT_SUCCESS);
		break;
	case 'O':
		env.output_file_suffix = arg;
		break;
	case ARGP_KEY_ARG:
		break;
	case ARGP_KEY_END:
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static const struct argp argp = {
	.options = opts,
	.parser = parse_arg,
	.doc = argp_prog_doc,
};

int default_create_blas(struct test *test)
{
	int version;

	CUBLAS_CHECK(cublasCreate(&test->handle), return -1);

	if (env.verbose) {
		CUBLAS_CHECK(cublasGetVersion(test->handle, &version), return -1);
		printf("BLAS version %d\n", version);
	}

	return 0;
}

int default_create_blasLt_type(struct test *test, cublasComputeType_t computeType,
				cudaDataType_t Atype, cudaDataType_t Btype,
				cudaDataType_t Ctype, cudaDataType_t scaleType)
{
	int rslt;

	CUBLAS_CHECK(cublasLtCreate(&test->ltHandle), exit(EXIT_FAILURE));

	CUBLAS_CHECK(cublasLtMatmulDescCreate(&test->matmulDesc, computeType, scaleType), exit(EXIT_FAILURE));

	CUBLAS_CHECK(cublasLtMatrixLayoutCreate(&test->layoutA, Atype, env.m, env.k, env.m), exit(EXIT_FAILURE));
	CUBLAS_CHECK(cublasLtMatrixLayoutCreate(&test->layoutB, Btype, env.k, env.n, env.k), exit(EXIT_FAILURE));
	CUBLAS_CHECK(cublasLtMatrixLayoutCreate(&test->layoutC, Ctype, env.m, env.n, env.m), exit(EXIT_FAILURE));
	CUDA_CHECK_EXIT(cudaMalloc(&test->workspace, test->workspaceSize));

	CUBLAS_CHECK(cublasLtMatmulPreferenceCreate(&test->pref), exit(EXIT_FAILURE));
	CUBLAS_CHECK(cublasLtMatmulPreferenceSetAttribute(test->pref,
			CUBLASLT_MATMUL_PREF_MAX_WORKSPACE_BYTES,
			&test->workspaceSize, sizeof(test->workspaceSize)), exit(EXIT_FAILURE));

	CUBLAS_CHECK(cublasLtMatmulAlgoGetHeuristic(test->ltHandle,
				test->matmulDesc,
				test->layoutA,
				test->layoutB,
				test->layoutC,
				test->layoutC,
				test->pref, 1, &test->heuristic_result, &rslt),);

	if (env.verbose) {
		if (rslt == 0) {
			fprintf(stderr, "No valid algorithm found! Using fallback method.\n");
		} else {
			printf("Found %d heuristic algorithms\n", rslt);
		}
		printf("BLAS version %zu\n", cublasLtGetVersion());
	}

	return 0;
}

int default_create_blasLt_int8(struct test *test)
{
	/**
	 * https://docs.nvidia.com/cuda/cublas/index.html#cublasltmatmul
	 *
	 * computeType: CUBLAS_COMPUTE_32I
	 * scaleType: CUDA_R_32I
	 * Atype/Btype: CUDA_R_8I
	 * Ctype: CUDA_R_32I
	 */
	return default_create_blasLt_type(test, CUBLAS_COMPUTE_32I,
		CUDA_R_8I, CUDA_R_8I, CUDA_R_32I, CUDA_R_32I);
}

int default_create_blasLt_int8_2(struct test *test)
{
	/**
	 * https://docs.nvidia.com/cuda/cublas/index.html#cublasltmatmul
	 *
	 * computeType: CUBLAS_COMPUTE_32I
	 * scaleType: CUDA_R_32F
	 * Atype/Btype/Ctype: CUDA_R_8I
	 */
	return default_create_blasLt_type(test, CUBLAS_COMPUTE_32I,
		CUDA_R_8I, CUDA_R_8I, CUDA_R_8I, CUDA_R_32F);
}

int default_create_blasLt_fp16(struct test *test)
{
	return default_create_blasLt_type(test, CUBLAS_COMPUTE_16F,
		CUDA_R_16F, CUDA_R_16F, CUDA_R_16F, CUDA_R_16F);
}

int default_create_blasLt_fp32(struct test *test)
{
	return default_create_blasLt_type(test, CUBLAS_COMPUTE_32F,
		CUDA_R_32F, CUDA_R_32F, CUDA_R_32F, CUDA_R_32F);
}

int default_create_blasLt_fp64(struct test *test)
{
	return default_create_blasLt_type(test, CUBLAS_COMPUTE_64F,
		CUDA_R_64F, CUDA_R_64F, CUDA_R_64F, CUDA_R_64F);
}

int __alloc_matrix_pair_int8(const char *dpfx, int8_t **host, int8_t **dev,
			     int x, int y)
{
	int i, j, err = 0;

	*host = (int8_t *)malloc(x * y * sizeof(int8_t));
	assert(*host && "Malloc failed");

	for (j = 0; j < y; j++) {
		if (env.verbose)
			printf("%s>> ", dpfx);
		for (i = 0; i < x; i++) {
			int8_t val = env.set_value ?
					(int8_t)env.value :
					(int8_t)(i * y + j + 1);
			(*host)[IDX2C(i, j, x)] = val;
			if (env.verbose)
				printf("%d\t", val);
		}
		if (env.verbose)
			printf("\n");
	}

	CUDA_CHECK(cudaMalloc(dev, x * y * sizeof(int8_t)), err = -ENOMEM);
	CUBLAS_CHECK(cublasSetMatrix(x, y, sizeof(int8_t), *host, x, *dev, x), err = -1);

	return err;
}

int __alloc_matrix_pair_int32(const char *dpfx, int32_t **host, int32_t **dev,
			     int x, int y)
{
	int i, j, err = 0;

	*host = (int32_t *)malloc(x * y * sizeof(int32_t));
	assert(*host && "Malloc failed");

	for (j = 0; j < y; j++) {
		if (env.verbose)
			printf("%s>> ", dpfx);
		for (i = 0; i < x; i++) {
			int32_t val = env.set_value ?
					(int32_t)env.value :
					(int32_t)(i * y + j + 1);
			(*host)[IDX2C(i, j, x)] = val;
			if (env.verbose)
				printf("%d\t", val);
		}
		if (env.verbose)
			printf("\n");
	}

	CUDA_CHECK(cudaMalloc(dev, x * y * sizeof(int32_t)), err = -ENOMEM);
	CUBLAS_CHECK(cublasSetMatrix(x, y, sizeof(int32_t), *host, x, *dev, x), err = -1);

	return err;
}

int __alloc_matrix_pair_fp16(const char *dpfx, half **host, half **dev,
			     int x, int y)
{
	int i, j, err = 0;

	*host = (half *)malloc(x * y * sizeof(half));
	assert(*host && "Malloc failed");

	for (j = 0; j < y; j++) {
		if (env.verbose)
			printf("%s>> ", dpfx);
		for (i = 0; i < x; i++) {
			float val = env.set_value ?
					(float)env.value :
					(float)(i * y + j + 1);
			(*host)[IDX2C(i, j, x)] = __float2half(val);
			if (env.verbose)
				printf("%.0f\t", val);
		}
		if (env.verbose)
			printf("\n");
	}

	CUDA_CHECK(cudaMalloc(dev, x * y * sizeof(half)), err = -ENOMEM);
	CUBLAS_CHECK(cublasSetMatrix(x, y, sizeof(half), *host, x, *dev, x), err = -1);

	return err;
}

int __alloc_matrix_pair_fp32(const char *dpfx, float **host, float **dev,
			     int x, int y)
{
	int i, j, err = 0;

	*host = (float *)malloc(x * y * sizeof(float));
	assert(*host && "Malloc failed");

	for (j = 0; j < y; j++) {
		if (env.verbose)
			printf("%s>> ", dpfx);
		for (i = 0; i < x; i++) {
			float val = env.set_value ?
					(float)env.value :
					(float)(i * y + j + 1);
			(*host)[IDX2C(i, j, x)] = val;
			if (env.verbose)
				printf("%.0f\t", val);
		}
		if (env.verbose)
			printf("\n");
	}

	CUDA_CHECK(cudaMalloc(dev, x * y * sizeof(float)), err = -ENOMEM);
	CUBLAS_CHECK(cublasSetMatrix(x, y, sizeof(float), *host, x, *dev, x), err = -1);

	return err;
}

int __alloc_matrix_pair_fp64(const char *dpfx, double **host, double **dev,
			     int x, int y)
{
	int i, j, err = 0;

	*host = (double *)malloc(x * y * sizeof(double));
	assert(*host && "Malloc failed");

	for (j = 0; j < y; j++) {
		if (env.verbose)
			printf("%s>> ", dpfx);
		for (i = 0; i < x; i++) {
			double val = env.set_value ?
					(double)env.value :
					(double)(i * y + j + 1);
			(*host)[IDX2C(i, j, x)] = val;
			if (env.verbose)
				printf("%.0lf\t", val);
		}
		if (env.verbose)
			printf("\n");
	}

	CUDA_CHECK(cudaMalloc(dev, x * y * sizeof(double)), err = -ENOMEM);
	CUBLAS_CHECK(cublasSetMatrix(x, y, sizeof(double), *host, x, *dev, x), err = -1);

	return err;
}

int prepare_data_matrix_A_fp64(struct test *test)
{
	return __alloc_matrix_pair_fp64("A fp64", &test->host_A.fp64, &test->dev_A.fp64, env.n, env.m);
}

int prepare_data_matrix_A_fp32(struct test *test)
{
	return __alloc_matrix_pair_fp32("A fp32", &test->host_A.fp32, &test->dev_A.fp32, env.n, env.m);
}

int prepare_data_matrix_sameAB_fp32(struct test *test)
{
	int err = 0;
	err += __alloc_matrix_pair_fp32("A fp32", &test->host_A.fp32, &test->dev_A.fp32, env.n, env.m);
	err += __alloc_matrix_pair_fp32("B fp32", &test->host_B.fp32, &test->dev_B.fp32, env.n, env.m);
	return err;
}

int prepare_data_matrix_sameAB_fp64(struct test *test)
{
	int err = 0;
	err += __alloc_matrix_pair_fp64("A fp64", &test->host_A.fp64, &test->dev_A.fp64, env.n, env.m);
	err += __alloc_matrix_pair_fp64("B fp64", &test->host_B.fp64, &test->dev_B.fp64, env.n, env.m);
	return err;
}

int prepare_data_matrix_ABint8_Cint32(struct test *test)
{
	int err = 0;
	err += __alloc_matrix_pair_int8("A int8", &test->host_A.int8, &test->dev_A.int8, env.k, env.m);
	err += __alloc_matrix_pair_int8("B int8", &test->host_B.int8, &test->dev_B.int8, env.n, env.k);
	err += __alloc_matrix_pair_int32("C int32", &test->host_C.int32, &test->dev_C.int32, env.n, env.m);
	return err;
}

int prepare_data_matrix_ABC_int8(struct test *test)
{
	int err = 0;
	err += __alloc_matrix_pair_int8("A int8", &test->host_A.int8, &test->dev_A.int8, env.k, env.m);
	err += __alloc_matrix_pair_int8("B int8", &test->host_B.int8, &test->dev_B.int8, env.n, env.k);
	err += __alloc_matrix_pair_int8("C int8", &test->host_C.int8, &test->dev_C.int8, env.n, env.m);
	return err;
}

int prepare_data_matrix_ABC_fp16(struct test *test)
{
	int err = 0;
	err += __alloc_matrix_pair_fp16("A fp16", &test->host_A.fp16, &test->dev_A.fp16, env.k, env.m);
	err += __alloc_matrix_pair_fp16("B fp16", &test->host_B.fp16, &test->dev_B.fp16, env.n, env.k);
	err += __alloc_matrix_pair_fp16("C fp16", &test->host_C.fp16, &test->dev_C.fp16, env.n, env.m);
	return err;
}

int prepare_data_matrix_ABC_fp32(struct test *test)
{
	int err = 0;
	err += __alloc_matrix_pair_fp32("A fp32", &test->host_A.fp32, &test->dev_A.fp32, env.k, env.m);
	err += __alloc_matrix_pair_fp32("B fp32", &test->host_B.fp32, &test->dev_B.fp32, env.n, env.k);
	err += __alloc_matrix_pair_fp32("C fp32", &test->host_C.fp32, &test->dev_C.fp32, env.n, env.m);
	return err;
}

int prepare_data_matrix_ABC_fp64(struct test *test)
{
	int err = 0;
	err += __alloc_matrix_pair_fp64("A fp64", &test->host_A.fp64, &test->dev_A.fp64, env.k, env.m);
	err += __alloc_matrix_pair_fp64("B fp64", &test->host_B.fp64, &test->dev_B.fp64, env.n, env.k);
	err += __alloc_matrix_pair_fp64("C fp64", &test->host_C.fp64, &test->dev_C.fp64, env.n, env.m);
	return err;
}

/**
 * A[j] = alpha * A[j]
 */
int run_blas_scal_fp32(struct test *test)
{
	float alpha = (float)(env.alpha);
	cublasSscal(test->handle, env.m * env.n, &alpha, test->dev_A.fp32, 1);
	return 0;
}

int run_blas_scal_fp64(struct test *test)
{
	double alpha = (double)(env.alpha);
	cublasDscal(test->handle, env.m * env.n, &alpha, test->dev_A.fp64, 1);
	return 0;
}

double get_flops_scal(struct test *test)
{
	return env.nloop * env.m * env.n * 1e3 / (test->run.elapsed);
}

/**
 * B[j] = alpha x A[k] + B[j]
 */
int run_blas_axpy_fp32(struct test *test)
{
	float alpha = (float)env.alpha;
	cublasSaxpy(test->handle, env.m * env.n, &alpha,
			test->dev_A.fp32, 1,
			test->dev_B.fp32, 1);
	return 0;
}

int run_blas_axpy_fp64(struct test *test)
{
	double alpha = (double)env.alpha;
	cublasDaxpy(test->handle, env.m * env.n, &alpha,
			test->dev_A.fp64, 1,
			test->dev_B.fp64, 1);
	return 0;
}

double get_flops_axpy(struct test *test)
{
	return 2.0 * env.nloop * env.m * env.n * 1e3 / (test->run.elapsed);
}

/**
 * B[j] = A[k]
 */
int run_blas_copy_fp32(struct test *test)
{
	cublasScopy(test->handle, env.m * env.n, test->dev_A.fp32, 1, test->dev_B.fp32, 1);
	return 0;
}

int run_blas_copy_fp64(struct test *test)
{
	cublasDcopy(test->handle, env.m * env.n, test->dev_A.fp64, 1, test->dev_B.fp64, 1);
	return 0;
}

double get_flops_copy(struct test *test)
{
	return env.nloop * env.m * env.n * 1e3 / (test->run.elapsed);
}

int run_blas_dot_fp32(struct test *test)
{
	cublasSdot(test->handle, env.m * env.n, test->dev_A.fp32, 1, test->dev_B.fp32, 1, &test->result.fp32);
	return 0;
}

int run_blas_dot_fp64(struct test *test)
{
	cublasDdot(test->handle, env.m * env.n, test->dev_A.fp64, 1, test->dev_B.fp64, 1, &test->result.fp64);
	return 0;
}

double get_flops_dot(struct test *test)
{
	return env.nloop * env.m * env.n * 1e3 / (test->run.elapsed);
}

int run_blas_nrm2_fp32(struct test *test)
{
	cublasSnrm2(test->handle, env.m * env.n, test->dev_A.fp32, 1, &test->result.fp32);
	return 0;
}

int run_blas_nrm2_fp64(struct test *test)
{
	cublasDnrm2(test->handle, env.m * env.n, test->dev_A.fp64, 1, &test->result.fp64);
	return 0;
}

double get_flops_nrm2(struct test *test)
{
	return env.nloop * (1 + env.m * env.n) * 1e3 / (test->run.elapsed);
}

int run_blas_GemmEx_int8(struct test *test)
{
	int32_t alpha = (int32_t)(env.alpha);
	int32_t beta = (int32_t)(env.beta);

	/**
	 * C^T = B^T * A^T equal to C = A * B
	 */
	CUBLAS_CHECK(cublasGemmEx(test->handle, CUBLAS_OP_T, CUBLAS_OP_T,
				env.m, env.n, env.k,
				&alpha,
				test->dev_A.int8, CUDA_R_8I, env.k,
				test->dev_B.int8, CUDA_R_8I, env.n,
				&beta,
				test->dev_C.int32, CUDA_R_32I, env.m,
				CUBLAS_COMPUTE_32I,
				CUBLAS_GEMM_DEFAULT),
			return -1);
	return 0;
}

int run_blas_GemmEx_fp16(struct test *test)
{
	half alpha = __float2half(env.alpha);
	half beta = __float2half(env.beta);

	/**
	 * C^T = B^T * A^T equal to C = A * B
	 */
	CUBLAS_CHECK(cublasGemmEx(test->handle, CUBLAS_OP_T, CUBLAS_OP_T,
				env.m, env.n, env.k,
				&alpha,
				test->dev_A.fp16, CUDA_R_16F, env.k,
				test->dev_B.fp16, CUDA_R_16F, env.n,
				&beta,
				test->dev_C.fp16, CUDA_R_16F, env.m,
				CUBLAS_COMPUTE_16F,
				CUBLAS_GEMM_DEFAULT),
			return -1);
	return 0;
}

int run_blas_GemmEx_fp32(struct test *test)
{
	float alpha = (float)(env.alpha);
	float beta = (float)(env.beta);

	/**
	 * C^T = B^T * A^T equal to C = A * B
	 */
	CUBLAS_CHECK(cublasGemmEx(test->handle, CUBLAS_OP_T, CUBLAS_OP_T,
				env.m, env.n, env.k,
				&alpha,
				test->dev_A.fp32, CUDA_R_32F, env.k,
				test->dev_B.fp32, CUDA_R_32F, env.n,
				&beta,
				test->dev_C.fp32, CUDA_R_32F, env.m,
				CUBLAS_COMPUTE_32F,
				CUBLAS_GEMM_DEFAULT),
			return -1);
	return 0;
}

int run_blas_GemmEx_fp64(struct test *test)
{
	double alpha = (double)(env.alpha);
	double beta = (double)(env.beta);

	/**
	 * C^T = B^T * A^T equal to C = A * B
	 */
	CUBLAS_CHECK(cublasGemmEx(test->handle, CUBLAS_OP_T, CUBLAS_OP_T,
				env.m, env.n, env.k,
				&alpha,
				test->dev_A.fp64, CUDA_R_64F, env.k,
				test->dev_B.fp64, CUDA_R_64F, env.n,
				&beta,
				test->dev_C.fp64, CUDA_R_64F, env.m,
				CUBLAS_COMPUTE_64F,
				CUBLAS_GEMM_DEFAULT),
			return -1);
	return 0;
}

int run_blas_Gemm_fp16(struct test *test)
{
	half alpha = __float2half(env.alpha);
	half beta = __float2half(env.beta);

	/**
	 * C^T = B^T * A^T equal to C = A * B
	 */
	CUBLAS_CHECK(cublasHgemm(test->handle, CUBLAS_OP_T, CUBLAS_OP_T,
				env.m, env.n, env.k,
				&alpha,
				test->dev_A.fp16, env.k,
				test->dev_B.fp16, env.n,
				&beta,
				test->dev_C.fp16, env.m),
			return -1);
	return 0;
}

int run_blas_Gemm_fp32(struct test *test)
{
	float alpha = (float)env.alpha;
	float beta = (float)env.beta;

	/**
	 * C^T = B^T * A^T equal to C = A * B
	 */
	CUBLAS_CHECK(cublasSgemm(test->handle, CUBLAS_OP_T, CUBLAS_OP_T,
				env.m, env.n, env.k,
				&alpha,
				test->dev_A.fp32, env.k,
				test->dev_B.fp32, env.n,
				&beta,
				test->dev_C.fp32, env.m),
			return -1);
	return 0;
}

int run_blas_Gemm_fp64(struct test *test)
{
	double alpha = (double)(env.alpha);
	double beta = (double)(env.beta);

	/**
	 * C^T = B^T * A^T equal to C = A * B
	 */
	CUBLAS_CHECK(cublasDgemm(test->handle, CUBLAS_OP_T, CUBLAS_OP_T,
				env.m, env.n, env.k,
				&alpha,
				test->dev_A.fp64, env.k,
				test->dev_B.fp64, env.n,
				&beta,
				test->dev_C.fp64, env.m),
			return -1);
	return 0;
}

/**
 * D = alpha * (A x B) + beta * (C)
 */
double get_flops_gemm(struct test *test)
{
	return 2.0 * env.nloop * env.k * env.m * env.n * 1e3 / (test->run.elapsed);
}

/**
 * D = alpha*(A*B) + beta*(C)
 *
 * type: 1-fp32, 2-fp16, 3-fp64, 4-int32
 */
static inline int run_blas_Matmul_type(struct test *test, int type)
{
	int32_t alpha_int32 = (int32_t)env.alpha;
	int32_t beta_int32 = (int32_t)env.beta;
	float alpha_fp32 = (float)env.alpha;
	float beta_fp32 = (float)env.beta;
	double alpha_fp64 = (double)env.alpha;
	double beta_fp64 = (double)env.beta;
	half alpha_fp16 = __float2half((float)env.alpha);
	half beta_fp16 = __float2half((float)env.beta);

	void *alpha, *beta;

	switch (type) {
	case 1:
		alpha = &alpha_fp32;
		beta = &beta_fp32;
		break;
	case 2:
		alpha = &alpha_fp16;
		beta = &beta_fp16;
		break;
	case 3:
		alpha = &alpha_fp64;
		beta = &beta_fp64;
		break;
	case 4:
		alpha = &alpha_int32;
		beta = &beta_int32;
		break;
	}

	CUBLAS_CHECK(cublasLtMatmul(
				test->ltHandle,
				test->matmulDesc,
				alpha,
				test->dev_A.ptr,
				test->layoutA,
				test->dev_B.ptr,
				test->layoutB,
				beta,
				test->dev_C.ptr,
				test->layoutC,
				test->dev_C.ptr,
				test->layoutC,
				&test->heuristic_result.algo,
				test->workspace,
				test->workspaceSize,
				NULL /* No stream */), return -1);
	return 0;
}

int run_blas_Matmul_int8(struct test *test)
{
	/**
	 * WARNING: alpha and beta need to be int32
	 * see https://docs.nvidia.com/cuda/cublas/index.html#cublasltmatmul
	 */
	return run_blas_Matmul_type(test, 4);
}

int run_blas_Matmul_int8_2(struct test *test)
{
	/**
	 * WARNING: alpha and beta need to be float
	 * see https://docs.nvidia.com/cuda/cublas/index.html#cublasltmatmul
	 */
	return run_blas_Matmul_type(test, 4);
}

int run_blas_Matmul_fp16(struct test *test)
{
	return run_blas_Matmul_type(test, 2);
}

int run_blas_Matmul_fp32(struct test *test)
{
	return run_blas_Matmul_type(test, 1);
}

int run_blas_Matmul_fp64(struct test *test)
{
	return run_blas_Matmul_type(test, 3);
}

int __display_matrix_pair_int8(const char *pfx, struct test *test,
			       int8_t *host, int8_t *dev, int x, int y)
{
	int i, j;
	long sum = 0;

	CUBLAS_CHECK(cublasGetMatrix(x, y, sizeof(int8_t), dev, x, host, x), return -1);

	fwrite_test(test, host, sizeof(int8_t), x * y);

	/* only print in verbose mode */
	if (!env.verbose)
		return 0;

	for (j = 0; j < y; j++) {
		printf("%s>> ", pfx);
		for (i = 0; i < x; i++) {
			sum += host[IDX2C(i, j, x)];
			printf("%7d", host[IDX2C(i, j, x)]);
		}
		printf("\n");
	}
	printf("%s>> Host sum %ld\n", pfx, sum);
	return 0;
}

int __display_matrix_pair_int32(const char *pfx, struct test *test,
			       int32_t *host, int32_t *dev, int x, int y)
{
	int i, j;
	long sum = 0;

	CUBLAS_CHECK(cublasGetMatrix(x, y, sizeof(int32_t), dev, x, host, x), return -1);

	fwrite_test(test, host, sizeof(int32_t), x * y);

	/* only print in verbose mode */
	if (!env.verbose)
		return 0;

	for (j = 0; j < y; j++) {
		printf("%s>> ", pfx);
		for (i = 0; i < x; i++) {
			sum += host[IDX2C(i, j, x)];
			printf("%7d", host[IDX2C(i, j, x)]);
		}
		printf("\n");
	}
	printf("%s>> Host sum %ld\n", pfx, sum);
	return 0;
}

int __display_matrix_pair_fp16(const char *pfx, struct test *test,
			       half *host, half *dev, int x, int y)
{
	int i, j;
	float sum = 0.0;

	CUBLAS_CHECK(cublasGetMatrix(x, y, sizeof(half), dev, x, host, x), return -1);

	fwrite_test(test, host, sizeof(half), x * y);

	/* only print in verbose mode */
	if (!env.verbose)
		return 0;

	for (j = 0; j < y; j++) {
		printf("%s>> ", pfx);
		for (i = 0; i < x; i++) {
			sum += __half2float(host[IDX2C(i, j, x)]);
			printf("%7.0f", __half2float(host[IDX2C(i, j, x)]));
		}
		printf("\n");
	}
	printf("%s>> Host sum %.2f\n", pfx, sum);
	return 0;
}

int __display_matrix_pair_fp32(const char *pfx, struct test *test,
			       float *host, float *dev, int x, int y)
{
	int i, j;
	int idx_max, idx_min;
	float sum = 0.0;

	CUBLAS_CHECK(cublasGetMatrix(x, y, sizeof(float), dev, x, host, x), return -1);

	fwrite_test(test, host, sizeof(float), x * y);

	/* only print in verbose mode */
	if (!env.verbose)
		return 0;

	cublasIsamax(test->handle, y * x, dev, 1, &idx_max);
	cublasIsamin(test->handle, y * x, dev, 1, &idx_min);
	cublasSasum(test->handle, y * x, dev, 1, &sum);

	printf("%s>> Device index min %d, index max %d, sum %.2f\n", pfx,
		idx_min, idx_max, sum);

	sum = 0;

	for (j = 0; j < y; j++) {
		printf("%s>> ", pfx);
		for (i = 0; i < x; i++) {
			sum += host[IDX2C(i, j, x)];
			printf("%7.0f", host[IDX2C(i, j, x)]);
		}
		printf("\n");
	}
	printf("%s>> Host sum %.2f\n", pfx, sum);
	return 0;
}

int __display_matrix_pair_fp64(const char *pfx, struct test *test,
			       double *host, double *dev, int x, int y)
{
	int i, j;
	int idx_max, idx_min;
	double sum = 0.0;

	CUBLAS_CHECK(cublasGetMatrix(x, y, sizeof(double), dev, x, host, x), return -1);

	fwrite_test(test, host, sizeof(double), x * y);

	/* only print in verbose mode */
	if (!env.verbose)
		return 0;

	cublasIdamax(test->handle, y * x, dev, 1, &idx_max);
	cublasIdamin(test->handle, y * x, dev, 1, &idx_min);
	cublasDasum(test->handle, y * x, dev, 1, &sum);

	printf("%s>> Device index min %d, index max %d, sum %.2f\n", pfx,
		idx_min, idx_max, sum);

	sum = 0;

	for (j = 0; j < y; j++) {
		printf("%s>> ", pfx);
		for (i = 0; i < x; i++) {
			sum += host[IDX2C(i, j, x)];
			printf("%7.0lf", host[IDX2C(i, j, x)]);
		}
		printf("\n");
	}
	printf("%s>> Host sum %.2lf\n", pfx, sum);
	return 0;
}

int display_data_A_fp32(struct test *test)
{
	return __display_matrix_pair_fp32("A fp32", test,
		test->host_A.fp32, test->dev_A.fp32, env.n, env.m);
}

int display_data_A_fp64(struct test *test)
{
	return __display_matrix_pair_fp64("A fp64", test,
		test->host_A.fp64, test->dev_A.fp64, env.n, env.m);
}

int display_data_AB_fp32(struct test *test)
{
	int err = 0;
	err += __display_matrix_pair_fp32("A fp32", test, test->host_A.fp32, test->dev_A.fp32, env.n, env.m);
	err += __display_matrix_pair_fp32("B fp32", test, test->host_B.fp32, test->dev_B.fp32, env.n, env.m);
	return err;
}

int display_data_AB_fp64(struct test *test)
{
	int err = 0;
	err += __display_matrix_pair_fp64("A fp64", test, test->host_A.fp64, test->dev_A.fp64, env.n, env.m);
	err += __display_matrix_pair_fp64("B fp64", test, test->host_B.fp64, test->dev_B.fp64, env.n, env.m);
	return err;
}

int display_data_ABint8_Cint32(struct test *test)
{
	int err = 0;
	err += __display_matrix_pair_int8("A int8", test, test->host_A.int8, test->dev_A.int8, env.k, env.m);
	err += __display_matrix_pair_int8("B int8", test, test->host_B.int8, test->dev_B.int8, env.n, env.k);
	err += __display_matrix_pair_int32("C int32", test, test->host_C.int32, test->dev_C.int32, env.n, env.m);
	return err;
}

int display_data_ABC_int8(struct test *test)
{
	int err = 0;
	err += __display_matrix_pair_int8("A int8", test, test->host_A.int8, test->dev_A.int8, env.k, env.m);
	err += __display_matrix_pair_int8("B int8", test, test->host_B.int8, test->dev_B.int8, env.n, env.k);
	err += __display_matrix_pair_int8("C int8", test, test->host_C.int8, test->dev_C.int8, env.n, env.m);
	return err;
}

int display_data_ABC_fp16(struct test *test)
{
	int err = 0;
	err += __display_matrix_pair_fp16("A fp16", test, test->host_A.fp16, test->dev_A.fp16, env.k, env.m);
	err += __display_matrix_pair_fp16("B fp16", test, test->host_B.fp16, test->dev_B.fp16, env.n, env.k);
	err += __display_matrix_pair_fp16("C fp16", test, test->host_C.fp16, test->dev_C.fp16, env.n, env.m);
	return err;
}

int display_data_ABC_fp32(struct test *test)
{
	int err = 0;
	err += __display_matrix_pair_fp32("A fp32", test, test->host_A.fp32, test->dev_A.fp32, env.k, env.m);
	err += __display_matrix_pair_fp32("B fp32", test, test->host_B.fp32, test->dev_B.fp32, env.n, env.k);
	err += __display_matrix_pair_fp32("C fp32", test, test->host_C.fp32, test->dev_C.fp32, env.n, env.m);
	return err;
}

int display_data_ABC_fp64(struct test *test)
{
	int err = 0;
	err += __display_matrix_pair_fp64("A fp64", test, test->host_A.fp64, test->dev_A.fp64, env.k, env.m);
	err += __display_matrix_pair_fp64("B fp64", test, test->host_B.fp64, test->dev_B.fp64, env.n, env.k);
	err += __display_matrix_pair_fp64("C fp64", test, test->host_C.fp64, test->dev_C.fp64, env.n, env.m);
	return err;
}

int free_data_matrix_A(struct test *test)
{
	cudaFree(test->dev_A.ptr);
	free(test->host_A.ptr);
	return 0;
}

int free_data_matrix_AB(struct test *test)
{
	cudaFree(test->dev_A.ptr);
	cudaFree(test->dev_B.ptr);
	free(test->host_A.ptr);
	free(test->host_B.ptr);
	return 0;
}

int free_data_matrix_ABC(struct test *test)
{
	cudaFree(test->dev_A.ptr);
	cudaFree(test->dev_B.ptr);
	cudaFree(test->dev_C.ptr);
	free(test->host_A.ptr);
	free(test->host_B.ptr);
	free(test->host_C.ptr);
	return 0;
}

int default_destroy_blas(struct test *test)
{
	cublasDestroy(test->handle);
	return 0;
}

int default_destroy_blasLt(struct test *test)
{
	cudaFree(test->workspace);
	cublasLtMatmulPreferenceDestroy(test->pref);
	cublasLtMatrixLayoutDestroy(test->layoutA);
	cublasLtMatrixLayoutDestroy(test->layoutB);
	cublasLtMatrixLayoutDestroy(test->layoutC);
	cublasLtMatmulDescDestroy(test->matmulDesc);
	cublasLtDestroy(test->ltHandle);
	return 0;
}

struct test alltests[] = {
	{
		ZERO_TEST("SCAL FP32", TEST_SCAL_FP32),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_A_fp32,
			.run_blas = run_blas_scal_fp32,
			.get_flops = get_flops_scal,
			.display_data = display_data_A_fp32,
			.free_data = free_data_matrix_A,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("SCAL FP64", TEST_SCAL_FP64),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_A_fp64,
			.run_blas = run_blas_scal_fp64,
			.get_flops = get_flops_scal,
			.display_data = display_data_A_fp64,
			.free_data = free_data_matrix_A,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("AXPY FP32", TEST_AXPY_FP32),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_sameAB_fp32,
			.run_blas = run_blas_axpy_fp32,
			.get_flops = get_flops_axpy,
			.display_data = display_data_AB_fp32,
			.free_data = free_data_matrix_AB,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("AXPY FP64", TEST_AXPY_FP64),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_sameAB_fp64,
			.run_blas = run_blas_axpy_fp64,
			.get_flops = get_flops_axpy,
			.display_data = display_data_AB_fp64,
			.free_data = free_data_matrix_AB,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("COPY FP32", TEST_COPY_FP32),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_sameAB_fp32,
			.run_blas = run_blas_copy_fp32,
			.get_flops = get_flops_copy,
			.display_data = display_data_AB_fp32,
			.free_data = free_data_matrix_AB,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("COPY FP64", TEST_COPY_FP64),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_sameAB_fp64,
			.run_blas = run_blas_copy_fp64,
			.get_flops = get_flops_copy,
			.display_data = display_data_AB_fp64,
			.free_data = free_data_matrix_AB,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("DOT FP32", TEST_DOT_FP32),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_sameAB_fp32,
			.run_blas = run_blas_dot_fp32,
			.get_flops = get_flops_dot,
			.display_data = display_data_AB_fp32,
			.free_data = free_data_matrix_AB,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("DOT FP64", TEST_DOT_FP64),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_sameAB_fp64,
			.run_blas = run_blas_dot_fp64,
			.get_flops = get_flops_dot,
			.display_data = display_data_AB_fp64,
			.free_data = free_data_matrix_AB,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("NRM2 FP32", TEST_NRM2_FP32),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_A_fp32,
			.run_blas = run_blas_nrm2_fp32,
			.get_flops = get_flops_nrm2,
			.display_data = display_data_A_fp32,
			.free_data = free_data_matrix_A,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("NRM2 FP64", TEST_NRM2_FP64),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_A_fp64,
			.run_blas = run_blas_nrm2_fp64,
			.get_flops = get_flops_nrm2,
			.display_data = display_data_A_fp64,
			.free_data = free_data_matrix_A,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("GEMM FP16", TEST_GEMM_FP16),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_ABC_fp16,
			.run_blas = run_blas_Gemm_fp16,
			.get_flops = get_flops_gemm,
			.display_data = display_data_ABC_fp16,
			.free_data = free_data_matrix_ABC,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("GEMM FP32", TEST_GEMM_FP32),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_ABC_fp32,
			.run_blas = run_blas_Gemm_fp32,
			.get_flops = get_flops_gemm,
			.display_data = display_data_ABC_fp32,
			.free_data = free_data_matrix_ABC,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("GEMM FP64", TEST_GEMM_FP64),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_ABC_fp64,
			.run_blas = run_blas_Gemm_fp64,
			.get_flops = get_flops_gemm,
			.display_data = display_data_ABC_fp64,
			.free_data = free_data_matrix_ABC,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("GEMMEx FP16", TEST_GEMMEX_FP16),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_ABC_fp16,
			.run_blas = run_blas_GemmEx_fp16,
			.get_flops = get_flops_gemm,
			.display_data = display_data_ABC_fp16,
			.free_data = free_data_matrix_ABC,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("GEMMEx FP32", TEST_GEMMEX_FP32),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_ABC_fp32,
			.run_blas = run_blas_GemmEx_fp32,
			.get_flops = get_flops_gemm,
			.display_data = display_data_ABC_fp32,
			.free_data = free_data_matrix_ABC,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("GEMMEx FP64", TEST_GEMMEX_FP64),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_ABC_fp64,
			.run_blas = run_blas_GemmEx_fp64,
			.get_flops = get_flops_gemm,
			.display_data = display_data_ABC_fp64,
			.free_data = free_data_matrix_ABC,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("GEMMEx INT8", TEST_GEMMEX_INT8),
		{
			.create_blas = default_create_blas,
			.prepare_data = prepare_data_matrix_ABint8_Cint32,
			.run_blas = run_blas_GemmEx_int8,
			.get_flops = get_flops_gemm,
			.display_data = display_data_ABint8_Cint32,
			.free_data = free_data_matrix_ABC,
			.destroy_blas = default_destroy_blas,
		}
	},
	{
		ZERO_TEST("MATMUL INT8", TEST_MATMUL_INT8),
		{
			.create_blas = default_create_blasLt_int8,
			.prepare_data = prepare_data_matrix_ABint8_Cint32,
			.run_blas = run_blas_Matmul_int8,
			.get_flops = get_flops_gemm,
			.display_data = display_data_ABint8_Cint32,
			.free_data = free_data_matrix_ABC,
			.destroy_blas = default_destroy_blasLt,
		}
	},
	{
		ZERO_TEST("MATMUL INT8 (2)", TEST_MATMUL_INT8_2),
		{
			.create_blas = default_create_blasLt_int8_2,
			.prepare_data = prepare_data_matrix_ABC_int8,
			.run_blas = run_blas_Matmul_int8_2,
			.get_flops = get_flops_gemm,
			.display_data = display_data_ABC_int8,
			.free_data = free_data_matrix_ABC,
			.destroy_blas = default_destroy_blasLt,
		}
	},
	{
		ZERO_TEST("MATMUL FP16", TEST_MATMUL_FP16),
		{
			.create_blas = default_create_blasLt_fp16,
			.prepare_data = prepare_data_matrix_ABC_fp16,
			.run_blas = run_blas_Matmul_fp16,
			.get_flops = get_flops_gemm,
			.display_data = display_data_ABC_fp16,
			.free_data = free_data_matrix_ABC,
			.destroy_blas = default_destroy_blasLt,
		}
	},
	{
		ZERO_TEST("MATMUL FP32", TEST_MATMUL_FP32),
		{
			.create_blas = default_create_blasLt_fp32,
			.prepare_data = prepare_data_matrix_ABC_fp32,
			.run_blas = run_blas_Matmul_fp32,
			.get_flops = get_flops_gemm,
			.display_data = display_data_ABC_fp32,
			.free_data = free_data_matrix_ABC,
			.destroy_blas = default_destroy_blasLt,
		}
	},
	{
		ZERO_TEST("MATMUL FP64", TEST_MATMUL_FP64),
		{
			.create_blas = default_create_blasLt_fp64,
			.prepare_data = prepare_data_matrix_ABC_fp64,
			.run_blas = run_blas_Matmul_fp64,
			.get_flops = get_flops_gemm,
			.display_data = display_data_ABC_fp64,
			.free_data = free_data_matrix_ABC,
			.destroy_blas = default_destroy_blasLt,
		}
	},
};

void exec_one_test(struct test *test)
{
	unsigned long n;

	if (env.verbose)
		printf("Testing %s\n", test->name);

	if (env.output_file_suffix) {
		int i;
		char file[512];
		snprintf(file, sizeof(file) - 1, "%s-%s", test->name, env.output_file_suffix);

		/* Replace the specify character with '_' */
		for (i = 0; i < strlen(file); i++) {
			if (strchr(" ()*&#$@^%`~\\/", file[i]))
				file[i] = '_';
		}
		test->output.fp = fopen(file, "w");
		test->output.file = strdup(file);
		if (!test->output.fp) {
			fprintf(stderr, "ERROR: Failed open %s\n", file);
			return;
		}
	}

	test->create.start = nsecs();
	test->ops.create_blas(test);
	test->create.end = nsecs();

	test->prepare.start = nsecs();
	test->ops.prepare_data(test);
	test->prepare.end = nsecs();

	cudaEventCreate(&test->run.start);
	cudaEventCreate(&test->run.end);
	cudaEventRecord(test->run.start);
	for (n = 0; n < env.nloop; n++)
		test->ops.run_blas(test);
	cudaEventRecord(test->run.end);
	cudaEventSynchronize(test->run.end);
	cudaEventElapsedTime(&test->run.elapsed, test->run.start, test->run.end);

	test->run.flops = test->ops.get_flops(test);

	test->display.start = nsecs();
	test->ops.display_data(test);
	test->display.end = nsecs();

	test->free.start = nsecs();
	test->ops.free_data(test);
	test->free.end = nsecs();

	test->destroy.start = nsecs();
	test->ops.destroy_blas(test);
	test->destroy.end = nsecs();

	if (test->output.fp) {
		fclose(test->output.fp);
		free(test->output.file);
	}

#define LAT(n) ((test->n.end - test->n.start) / 1000000UL)
#define LAT_GPU(e) (test->e.elapsed)
	if (env.verbose) {
		printf("create elapsed %ld ms\n", LAT(create));
		printf("prepare elapsed %ld ms\n", LAT(prepare));
		printf("display elapsed %ld ms\n", LAT(display));
		printf("free elapsed %ld ms\n", LAT(free));
	}
	printf("%s elapsed %.2f ms, %.2lf FLOPS/OPS, %.2lf GFLOPS/GOPS, %.2lf TFLOPS/TOPS\n",
		test->name,
		LAT_GPU(run),
		test->run.flops,
		test->run.flops / 1e9,
		test->run.flops / 1e12);
#undef LAT
#undef LAT_GPU
}

int main(int argc, char *argv[])
{
	int i, err = 0;
	struct test *test;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	gpu_init(0);

	if (env.verbose) {
		print_version();
		printf("M = %ld, N = %ld\n", env.m, env.n);
		if (env.output_file_suffix)
			fprintf(stderr, "Output file %s\n", env.output_file_suffix);
	}

	for (i = 0; i < ARRAY_SIZE(alltests); i++) {
		test = &alltests[i];
		if (env.test_type != TEST_ALL && env.test_type != test->type)
			continue;
		exec_one_test(test);
	}

	return 0;
}
