// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * Using GPU to perform matrix multiplication, and this program not use any
 * library(like BLAS), only use pure-C to test matrix.
 *
 * - commit 2506e482755d ("hpc: matrix-mul: Nvidia Tesla T4 vs MetaX ???")
 * - commit 0528d8ab981f ("hpc: matrix-mul: Compare Nvidia H800 & Mars X203 (Metax)")
 */
#include <argp.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include <time.h>

/* Compatiable CUDA software stack */
#if defined(__NVCC__) || defined(__HIPCC__) || defined(__HPCC__) || defined(__LUCA__)
# define SUPPORT_CUDA_SYNOPSIS	1
#include "cuda_compat.h"
#include "cuda_helpers.h"
#else	/* pure C */
# define __global__
# define __device__
# define gpu_name(devid, b, bl)	({ strncpy(b, "CPU", bl); b; })
# define gpu_init(dev) do {} while (0)
#endif

#if defined(TEST_FP64)
# define TYPE	double
# define TNAME	"double"
# define TPFMT	"%.2lf"			/* print format */
# define TPVAL(v)	(v)		/* print value */
# define TRVAL(v)	(v * 1.0)	/* right value */
#elif defined(TEST_INT8)
# define TYPE	int8_t
# define TNAME	"int8_t"
# define TPFMT	"%d"
# define TPVAL(v)	(v)
# define TRVAL(v)	((int8_t)v)
#elif defined(TEST_FP16)
# define TYPE	half
# define TNAME	"half"
# define TPFMT	"%.2f"
# define TPVAL(v)	__half2float(v)
# define TRVAL(v)	__float2half(v)
#elif defined(TEST_FP32)
# define TYPE	float
# define TNAME	"float"
# define TPFMT	"%.2f"
# define TPVAL(v)	(v)
# define TRVAL(v)	(v * 1.0f)
#else
# error "ERROR: Must define one of TEST_FP16, TEST_FP32, TEST_FP64, TEST_INT8"
#endif

#define NS2US	1000UL
#define MAX(x, y)	(x > y ? x : y)

struct {
	union {
		int gpu;
		int cpu;
	} core;
	/* use 2D grid and block */
	bool dim_2;
	bool verbose;
	unsigned long m, k, n;
	bool vector;
	unsigned long nloop;
	TYPE alpha, beta;
	bool set_value;
	unsigned long value;
	unsigned int unit_time;
	struct {
		char *file;
		bool is_txt;	/* output as text instead of binary */
	} output;
} env = {
	.core = {
		.gpu = 0,
	},
	.dim_2 = false,
	.verbose = false,
	.m = 2,
	.k = 3,
	.n = 2,
	.vector = false,
	.nloop = 1,
	.alpha = TRVAL(1),
	.beta = TRVAL(1),
	.set_value = false,
	.value = 0,
	.unit_time = NS2US,
	.output = {
		.file = NULL,
		.is_txt = false,
	},
};

const char *version = "v1.0.3 "
#if defined(__HPCC__)
	"(GPU MetaX)"
#elif defined(__LUCA__)
	"(GPU CESTC)"
#elif defined(__HIPCC__)
	"(GPU AMD)"
#elif defined(__NVCC__)
	"(GPU Nvidia)"
#else
	"(CPU)"
#endif
;

const char argp_prog_doc[] =
	"USAGE: [-m <NUM>] [-n <NUM>] [--nloop|-N <NUM>] [-i <VAL>] [-2] [-v]\n"
	"\n"
	"Examples:\n"
	" $ time ./matrix-mul -m200 -n200 -N10000 -i2";

static const struct argp_option opts[] = {
	{ "gpu", 'g', "GPU", 0, "Running on GPU" },
	{ "2dim", '2', NULL, 1, "Use 2D grid and block of GPU" },
	{ "vector", 'z', NULL, 1, "Call vector instead of matrix" },
	{ "m-num", 'm', "M_NUM", 0, "Matrix M number" },
	{ "k-num", 'k', "K_NUM", 0, "Matrix K number" },
	{ "n-num", 'n', "N_NUM", 0, "Matrix N number" },
	{ "alpha", 'a', "ALPHA", 0, "Alpha number" },
	{ "beta", 'b', "BETA", 0, "Beta number" },
	{ "nloop", 'N', "NLOOP", 0, "Test loop number" },
	{ "init-val", 'i', "INIT_VAL", 0, "Set matrix values" },
	{ "verbose", 'v', NULL, 1, "Display detail" },
	{ "version", 'V', NULL, 1, "Display version" },
	{ "output-file", 'O', "FILE", 0, "Specify output file name" },
	{ "output-txt", 'T', NULL, 1, "Output text file instead binary" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'g':
		env.core.gpu = strtoul(arg, NULL, 10);
		break;
	case '2':
		env.dim_2 = true;
		break;
	case 'm':
		env.m = strtoul(arg, NULL, 10);
		break;
	case 'k':
		env.k = strtoul(arg, NULL, 10);
		break;
	case 'n':
		env.n = strtoul(arg, NULL, 10);
		break;
	case 'a':
		env.alpha = TRVAL(strtoul(arg, NULL, 10));
		break;
	case 'b':
		env.beta = TRVAL(strtoul(arg, NULL, 10));
		break;
	case 'N':
		env.nloop = strtoul(arg, NULL, 10);
		break;
	case 'i':
		env.set_value = true;
		env.value = strtoul(arg, NULL, 10);
		break;
	case 'z':
		env.vector = true;
		break;
	case 'v':
		env.verbose = true;
		break;
	case 'V':
		printf("%s\n", version);
		exit(EXIT_SUCCESS);
		break;
	case 'O':
		env.output.file = arg;
		break;
	case 'T':
		env.output.is_txt = true;
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

static inline unsigned long nsecs(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000000000UL + ts.tv_nsec;
}

/**
 * alpha * A[m*k] * B[k*n] + beta * C[m*n] = D[m*n]
 *
 * m=2,k=3,n=2 alpha=1,beta=1
 *
 *                     ┌     ┐
 *         ┌       ┐   │ 1 2 │       ┌     ┐   ┌       ┐
 *         │ 1 2 3 │   │     │       │ 1 2 │   │ 23 30 │
 *     1 * │       │ * │ 3 4 │ + 1 * │     │ = │       │
 *         │ 4 5 6 │   │     │       │ 3 4 │   │ 52 68 │
 *         └       ┘   │ 5 6 │       └     ┘   └       ┘
 *                     └     ┘
 *
 * @nocal - The call of GPU kernel function will have a large overhead. When
 * nocal is true, multiplication operation will not be calculated, and a more
 * accurate FLOPS can be calculated.
 */

__device__ void dev_matrix_mul_inner(TYPE *A, TYPE *B, TYPE *C, TYPE *D,
			   TYPE alpha, TYPE beta,
			   unsigned long m, unsigned long im,
			   unsigned long k,
			   unsigned long n, unsigned long in,
			   bool nocal)
{
	unsigned long ia, ib, ik;
	unsigned long ic = im * n + in;

	if (!nocal) {
		D[ic] = TRVAL(0.0f);
	}

	for (ik = 0; ik < k; ik++) {
		ia = im * k + ik;
		ib = ik * n + in;
		if (!nocal) {
#if defined(TEST_FP16)
			D[ic] = __hadd(D[ic], __hmul(alpha, __hmul(A[ia], B[ib])));
#else
			D[ic] += TPVAL(alpha) * A[ia] * B[ib];
#endif
		}
	}
	if (!nocal) {
#if defined(TEST_FP16)
		D[ic] = __hadd(D[ic], __hmul(beta, C[ic]));
#else
		D[ic] += TPVAL(beta) * C[ic];
#endif
	}
}

__global__ void matrix_mul(TYPE *A, TYPE *B, TYPE *C, TYPE *D,
			   TYPE alpha, TYPE beta,
			   unsigned long m, unsigned long k,
			   unsigned long n, bool nocal)
{
	unsigned long ic, in, im;

#if defined(SUPPORT_CUDA_SYNOPSIS)
	ic = threadIdx.x + blockDim.x * blockIdx.x;
	if (ic >= m * n)
		return;
#else /* Running on CPU */
	for (ic = 0; ic < m * n; ic++)
#endif
	{
		in = ic % n;
		im = ic / n;

		dev_matrix_mul_inner(A, B, C, D, alpha, beta, m, im, k, n, in, nocal);
	}
#if defined(SUPPORT_CUDA_SYNOPSIS)
	__syncthreads();
#endif
}

__global__ void matrix_mul_2d(TYPE *A, TYPE *B, TYPE *C, TYPE *D,
			      TYPE alpha, TYPE beta,
			      unsigned long m, unsigned long k,
			      unsigned long n, bool nocal)
{
	unsigned long in, im;

#if defined(SUPPORT_CUDA_SYNOPSIS)
	in = threadIdx.x + blockDim.x * blockIdx.x;
	im = threadIdx.y + blockDim.y * blockIdx.y;
	if (in >= n || im >= m)
		return;
	{
#else /* Running on CPU */
	unsigned long ic;
	for (ic = 0; ic < m * n; ic++) {
		in = ic % n;
		im = ic / n;
#endif
		dev_matrix_mul_inner(A, B, C, D, alpha, beta, m, im, k, n, in, nocal);
	}
#if defined(SUPPORT_CUDA_SYNOPSIS)
	__syncthreads();
#endif
}

static double matrix_mul_FLOPS(unsigned long ns)
{
	/**
	 * 3.0: alpha + plus + A*B
	 */
	double part1 = 3.0 * env.m * env.k * env.n * env.nloop;
	/**
	 * 2.0: plus + beta*C
	 */
	double part2 = 2.0 * env.m * env.n * env.nloop;
	/**
	 * 1e9: nanoseconds to seconds
	 */
	return (part1 + part2) * 1e9 / ns;
}

/**
 * Vector multiplication
 */
__global__ void vector_mul(TYPE *A, TYPE *B, TYPE *C, TYPE alpha,
			       unsigned long N, bool nocal)
{
	unsigned long i;

#if defined(SUPPORT_CUDA_SYNOPSIS)
	i = threadIdx.x + blockDim.x * blockIdx.x;
	if (i >= N)
		return;
#else
	for (i = 0; i < N; i++)
#endif
	{
		if (!nocal) {
#if defined(TEST_FP16)
			C[i] = __hmul(alpha, __hmul(A[i], B[i]));
#else
			C[i] = alpha * A[i] * B[i];
#endif
		}
	}
#if defined(SUPPORT_CUDA_SYNOPSIS)
	__syncthreads();
#endif
}

static double vector_mul_FLOPS(unsigned long ns)
{
	/**
	 * 2.0: alpha + A*B
	 * 1e9: nanoseconds to seconds
	 */
	return 2.0 * env.m * env.k * env.nloop * 1e9 / ns;
}

void init_matrix(TYPE *p, unsigned long n, bool zero)
{
	int i;
	for (i = 0; i < n; i++) {
		if (zero)
			p[i] = TRVAL(0.0f);
		else if (env.set_value)
			p[i] = TRVAL(env.value);
		else
			p[i] = TRVAL(i + 1);
#ifdef DEBUG
		printf("p[%d] = " TPFMT "\n", i, TPVAL(p[i]));
#endif
	}
}

void print_matrix(TYPE *p, unsigned long x, unsigned long y)
{
	int i, j;
	for (j = 0; j < y; j++) {
		for (i = 0; i < x; i++) {
#ifdef DEBUG2
			printf("[%d,%d] = " TPFMT "\n", i, j, TPVAL(p[j * x + i]));
#else
			printf(TPFMT"\t", TPVAL(p[j * x + i]));
#endif
		}
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	unsigned long iloop, i;
	unsigned long start, cal_ns, total_ns;
	int err = 0;
	double flops;
#if defined(SUPPORT_CUDA_SYNOPSIS)
	unsigned long malloc_ns, h2d_ns, d2h_ns, kern_gpu_ns, kern_nocal_ns;
	TYPE *dev_A, *dev_B, *dev_C, *dev_D;
	cudaEvent_t ev_start, ev_stop;
	dim3 block1, block2;
	dim3 grid1, grid2;
#endif
	TYPE *host_A, *host_B, *host_C, *host_D;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (env.vector) {
		unsigned long _i = MAX(env.n, MAX(env.m, env.k));
		env.k = env.n = env.m = _i;
	}

	if (env.verbose) {
		char buf[64];
		fprintf(stderr, "Version %s\n", version);
		fprintf(stderr, "Running on %s %d\n", gpu_name(env.core.gpu, buf, sizeof(buf)), env.core.gpu);
		fprintf(stderr, "size of TYPE(%s) %ld\n", TNAME, sizeof(TYPE));
		fprintf(stderr, "M = %ld, K = %ld, N = %ld, NLOOP = %ld\n",
			env.m, env.k, env.n, env.nloop);
		if (env.set_value)
			fprintf(stderr, "Matrix values set to %ld\n", env.value);
		if (env.vector)
			fprintf(stderr, "Test vector instead of matrix\n");
		if (env.dim_2)
			fprintf(stderr, "Use 2D grid and block instead of 1D\n");
		if (env.output.file)
			fprintf(stderr, "Output file %s\n", env.output.file);
	}

	gpu_init(env.core.gpu);

	host_A = (TYPE *)malloc(sizeof(TYPE) * env.m * env.k);
	host_B = (TYPE *)malloc(sizeof(TYPE) * env.k * env.n);
	host_C = (TYPE *)malloc(sizeof(TYPE) * env.m * env.n);
	host_D = (TYPE *)malloc(sizeof(TYPE) * env.m * env.n);
	if (!host_A || !host_B || !host_C || !host_D)
		goto Malloc_failed;

	init_matrix(host_A, env.m * env.k, false);
	init_matrix(host_B, env.k * env.n, false);
	init_matrix(host_C, env.m * env.n, false);
	init_matrix(host_D, env.m * env.n, true);

#ifdef DEBUG
	print_matrix(host_A, env.k, env.m);
	print_matrix(host_B, env.n, env.k);
	print_matrix(host_C, env.n, env.m);
#endif

#if defined(SUPPORT_CUDA_SYNOPSIS)

	block1.x = 512;
	grid1.x = (env.m * env.n + block1.x - 1) / block1.x;

	/**
	 * Threads are batched in groups that we’ll call Wavefronts or waves
	 * (or warps in Nvidia lingo). Like the name, the numbers of threads
	 * in a wave is architecture dependent, 32 on NVIDIA GPUs, 64 on AMD’s
	 * GCN and variable on Intel cards.
	 * https://flashypixels.wordpress.com/2018/11/10/intro-to-gpu-scalarization-part-1/
	 */
	block2.x = 32;
	block2.y = 32;
	grid2.x = (env.n + block2.x - 1) / block2.x;
	grid2.y = (env.m + block2.y - 1) / block2.y;

	cudaEventCreate(&ev_start);
	cudaEventCreate(&ev_stop);

	start = nsecs();

	CUDA_CHECK(cudaMalloc(&dev_A, sizeof(TYPE) * env.m * env.k), goto Malloc_failed);
	CUDA_CHECK(cudaMalloc(&dev_B, sizeof(TYPE) * env.k * env.n), goto Malloc_failed);
	CUDA_CHECK(cudaMalloc(&dev_C, sizeof(TYPE) * env.m * env.n), goto Malloc_failed);
	CUDA_CHECK(cudaMalloc(&dev_D, sizeof(TYPE) * env.m * env.n), goto Malloc_failed);

	cudaMemset(dev_A, 0, sizeof(TYPE) * env.m * env.k);
	cudaMemset(dev_B, 0, sizeof(TYPE) * env.k * env.n);
	cudaMemset(dev_C, 0, sizeof(TYPE) * env.m * env.n);
	cudaMemset(dev_D, 0, sizeof(TYPE) * env.m * env.n);

	malloc_ns = nsecs() - start;

	start = nsecs();
	cudaMemcpy(dev_A, host_A, sizeof(TYPE) * env.m * env.k, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_B, host_B, sizeof(TYPE) * env.k * env.n, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_C, host_C, sizeof(TYPE) * env.m * env.n, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_D, host_D, sizeof(TYPE) * env.m * env.n, cudaMemcpyHostToDevice);
	h2d_ns = nsecs() - start;
#endif

	start = nsecs();
#if defined(SUPPORT_CUDA_SYNOPSIS)
	cudaEventRecord(ev_start, NULL);
#endif

	/* Stress test */
	for (iloop = 0; iloop < env.nloop; iloop++) {
#if defined(SUPPORT_CUDA_SYNOPSIS)
# define DIM	<<<grid1, block1>>>
# define DIM2	<<<grid2, block2>>>

		if (env.vector)
			vector_mul DIM (dev_A, dev_B, dev_C, env.alpha,
					env.m * env.n, false);
		else {
			if (env.dim_2) {
				matrix_mul_2d DIM2 (dev_A, dev_B, dev_C, dev_D,
						    env.alpha, env.beta,
						    env.m, env.k, env.n, false);
			} else {
				matrix_mul DIM (dev_A, dev_B, dev_C, dev_D,
						env.alpha, env.beta,
						env.m, env.k, env.n, false);
			}
		}
#else
		if (env.vector)
			vector_mul(host_A, host_B, host_C, env.alpha,
				   env.m * env.n, false);
		else
			matrix_mul(host_A, host_B, host_C, host_D,
				   env.alpha, env.beta,
				   env.m, env.k, env.n, false);
#endif
	}

#if defined(SUPPORT_CUDA_SYNOPSIS)
	cudaEventRecord(ev_stop, NULL);
	cudaEventSynchronize(ev_stop);
	float t_ms;
	cudaEventElapsedTime(&t_ms, ev_start, ev_stop);
	kern_gpu_ns = t_ms * 1e6;
#endif
	cal_ns = nsecs() - start;

#if defined(SUPPORT_CUDA_SYNOPSIS)
	/**
	 * The call of GPU kernel function will have a large overhead.
	 */
	cudaEventRecord(ev_start, NULL);

	for (iloop = 0; iloop < env.nloop; iloop++) {
		if (env.vector)
			vector_mul DIM (dev_A, dev_B, dev_C, env.alpha,
					env.m * env.n, true);
		else {
			if (env.dim_2) {
				matrix_mul_2d DIM2 (dev_A, dev_B, dev_C, dev_D,
						    env.alpha, env.beta,
						    env.m, env.k, env.n, true);
			} else {
				matrix_mul DIM (dev_A, dev_B, dev_C, dev_D,
						env.alpha, env.beta,
						env.m, env.k, env.n, true);
			}
		}
	}

	cudaEventRecord(ev_stop, NULL);
	cudaEventSynchronize(ev_stop);
	cudaEventElapsedTime(&t_ms, ev_start, ev_stop);
	kern_nocal_ns = t_ms * 1e6;
#endif


#if defined(SUPPORT_CUDA_SYNOPSIS)
	start = nsecs();
	cudaMemcpy(host_C, dev_C, sizeof(TYPE) * env.m * env.n, cudaMemcpyDeviceToHost);
	cudaMemcpy(host_D, dev_D, sizeof(TYPE) * env.m * env.n, cudaMemcpyDeviceToHost);
	d2h_ns = nsecs() - start;
#endif

#ifdef DEBUG
	print_matrix(host_C, env.n, env.m);
	print_matrix(host_D, env.n, env.m);
#endif

	/**
	 * If a fixed value is set, we can easily judge the accuracy of the
	 * calculation result.
	 */
	if (env.set_value) {
		double correct_val;
		TYPE *pv;
		if (env.vector) {
			correct_val = TPVAL(env.alpha) * env.value * env.value;
			pv = host_C;
		} else {
			correct_val = TPVAL(env.alpha) * env.value * env.value * env.k
					+ TPVAL(env.beta) * env.value;
			pv = host_D;
		}
		for (i = 0; i < env.m * env.n; i++) {
#ifdef DEBUG
			printf("correct_val %lf\n", correct_val);
#endif
			if ((double)TPVAL(pv[i]) != correct_val) {
				fprintf(stderr, "ERROR: cal matrix mul failed.\n");
				err = -1;
				break;
			}
		}
	}

#if defined(SUPPORT_CUDA_SYNOPSIS)
	cudaFree(dev_A);
	cudaFree(dev_B);
	cudaFree(dev_C);
	cudaFree(dev_D);

	cudaEventDestroy(ev_start);
	cudaEventDestroy(ev_stop);
#endif

	if (env.output.file) {
		FILE *fp = fopen(env.output.file, "w");
		if (env.output.is_txt) {
			size_t i;
			for (i = 0; i < env.m * env.k; i++)
				fprintf(fp, "%-8ld\t" TPFMT "\n", i, TPVAL(host_A[i]));
			for (i = 0; i < env.k * env.n; i++)
				fprintf(fp, "%-8ld\t" TPFMT "\n", i, TPVAL(host_B[i]));
			for (i = 0; i < env.m * env.n; i++)
				fprintf(fp, "%-8ld\t" TPFMT "\n", i, TPVAL(host_C[i]));
			for (i = 0; i < env.m * env.n; i++)
				fprintf(fp, "%-8ld\t" TPFMT "\n", i, TPVAL(host_D[i]));
		} else {
			fwrite(host_A, sizeof(TYPE), env.m * env.k, fp);
			fwrite(host_B, sizeof(TYPE), env.k * env.n, fp);
			fwrite(host_C, sizeof(TYPE), env.m * env.n, fp);
			fwrite(host_D, sizeof(TYPE), env.m * env.n, fp);
		}
		fclose(fp);
	}

	free(host_A);
	free(host_B);
	free(host_C);
	free(host_D);

	if (env.verbose) {
		printf("%-4s %-4s %-4s %-8s ", "M", "K", "N", "NLOOP");
#if defined(SUPPORT_CUDA_SYNOPSIS)
		printf("%-8s %-8s ", "ALLOC", "H2D");
#endif
		printf("%-12s ", "CAL");
#if defined(SUPPORT_CUDA_SYNOPSIS)
		printf("%-12s ", "KERN_NOCAL");
		printf("%-12s ", "KERN_GPU");
		printf("%-12s ", "D2H");
#endif
		printf("%-12s %-8s\n", "TOTAL", "GFLOPS");
	}

	total_ns = 0;
	printf("%-4ld %-4ld %-4ld %-8ld ", env.m, env.k, env.n, env.nloop);
#if defined(SUPPORT_CUDA_SYNOPSIS)
	total_ns += malloc_ns + h2d_ns;
	printf("%-8ld %-8ld ", malloc_ns / env.unit_time, h2d_ns / env.unit_time);
#endif
	total_ns += cal_ns;
	printf("%-12ld ", cal_ns / env.unit_time);
#if defined(SUPPORT_CUDA_SYNOPSIS)
	printf("%-12ld ", kern_nocal_ns / env.unit_time);
	printf("%-12ld ", kern_gpu_ns / env.unit_time);
	total_ns += d2h_ns;
	printf("%-12ld ", d2h_ns / env.unit_time);
#endif
	printf("%-12ld ", total_ns / env.unit_time);

	unsigned long flops_ns;
#if defined(SUPPORT_CUDA_SYNOPSIS)
	flops_ns = kern_gpu_ns; /* Contain kernel call latency */
#else
	flops_ns = cal_ns;
#endif
	if (env.vector)
		flops = vector_mul_FLOPS(flops_ns);
	else
		flops = matrix_mul_FLOPS(flops_ns);
	printf("%-8.2lf\n", flops / 1e9);

	return 0;

Malloc_failed:
	fprintf(stderr, "ERROR: Malloc failed.\n");
	return err;
}
