// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Metax has CUDA-compatible APIs */
#pragma once

#define cudaError_t	hcError_t
#define cudaSuccess	hcSuccess

#define cudaMalloc(pp, sz)	hcMalloc(pp, sz)
#define cudaFree(ptr)	hcFree(ptr)
#define cudaMemset(ptr, v, size)	hcMemset(ptr, v, size)
#define cudaMemcpy(dev, host, size, flag)	hcMemcpy(dev, host, size, flag)
#define cudaMemcpyHostToDevice	hcMemcpyHostToDevice
#define cudaMemcpyDeviceToHost	hcMemcpyDeviceToHost

#define cudaEvent_t	hcEvent_t
#define cudaEventCreate(pe)	hcEventCreate(pe)
#define cudaEventDestroy(ev)	hcEventDestroy(ev)
#define cudaEventRecord(ev)	hcEventRecord(ev)
#define cudaEventElapsedTime(pt, start, stop)	hcEventElapsedTime(pt, start, stop)
#define cudaEventSynchronize(ev)	hcEventSynchronize(ev)

#define cudaGetDeviceProperties(prop, devid)	hcGetDeviceProperties(prop, devid)

#define cudaDeviceGetP2PAttribute(v, attr, src, dst)	hcDeviceGetP2PAttribute(v, attr, src, dst)
#define cudaDevP2PAttrPerformanceRank	hcDevP2PAttrPerformanceRank
#define cudaDevP2PAttrAccessSupported	hcDevP2PAttrAccessSupported
#define cudaDevP2PAttrNativeAtomicSupported	hcDevP2PAttrNativeAtomicSupported

#define cudaDeviceSynchronize()	hcDeviceSynchronize()

/**
 * BLAS: Basic Linear Algebra Subprograms
 * see /usr/local/cuda-12.9/targets/x86_64-linux/include/cublas_api.h
 *
 * refs:
 * - https://docs.nvidia.com/cuda/cublas/index.html
 */
#define cublasStatus_t	hcblasStatus_t
#define CUBLAS_STATUS_SUCCESS	HCBLAS_STATUS_SUCCESS
#define CUBLAS_STATUS_NOT_INITIALIZED	HCBLAS_STATUS_NOT_INITIALIZED
#define CUBLAS_STATUS_ALLOC_FAILED	HCBLAS_STATUS_ALLOC_FAILED
#define CUBLAS_STATUS_INVALID_VALUE	HCBLAS_STATUS_INVALID_VALUE
#define CUBLAS_STATUS_ARCH_MISMATCH	HCBLAS_STATUS_ARCH_MISMATCH
#define CUBLAS_STATUS_MAPPING_ERROR	HCBLAS_STATUS_MAPPING_ERROR
#define CUBLAS_STATUS_EXECUTION_FAILED	HCBLAS_STATUS_EXECUTION_FAILED
#define CUBLAS_STATUS_INTERNAL_ERROR	HCBLAS_STATUS_INTERNAL_ERROR
#define CUBLAS_STATUS_NOT_SUPPORTED	HCBLAS_STATUS_NOT_SUPPORTED

#define cublasHandle_t	hcblasHandle_t
#define cublasCreate(handle)	hcblasCreate(handle)
#define cublasDestroy(handle)	hcblasDestroy(handle)

#define cublasGetVersion(handle, pversion)	hcblasGetVersion(handle, pversion)
#define cublasGetProperty(type, pvalue)	hcblasGetProperty(type, pvalue)

#define cublasOperation_t	hcblasOperation_t
#define CUBLAS_OP_N	HCBLAS_OP_N
#define CUBLAS_OP_T	HCBLAS_OP_T
#define CUBLAS_OP_C	HCBLAS_OP_C
#define CUBLAS_OP_HERMITAN	HCBLAS_OP_HERMITAN
#define CUBLAS_OP_CONJG	HCBLAS_OP_CONJG

#define cublasFillMode_t	hcblasFillMode_t
#define CUBLAS_FILL_MODE_LOWER	HCBLAS_FILL_MODE_LOWER
#define CUBLAS_FILL_MODE_UPPER	HCBLAS_FILL_MODE_UPPER
#define CUBLAS_FILL_MODE_FULL	HCBLAS_FILL_MODE_FULL

#define cublasSetMatrix(rows, cols, elemsize, A, ola, B, ldb)	\
	hcblasSetMatrix(rows, cols, elemsize, A, ola, B, ldb)
#define cublasGetMatrix(rows, cols, elemsize, A, ola, B, ldb)	\
	hcblasGetMatrix(rows, cols, elemsize, A, ola, B, ldb)

/**
 * x[j] = alpha * x[j]
 * i = 1 ... n
 * j = 1 + (i − 1) * incx
 *
 * S-float, D-double, C-Complex, Cs-Complex/float, Z-DoubleComplex, Zd-DoubleComplex/double
 */
#define cublasSscal(handle, n, alpha, x, incx)	hcblasSscal(handle, n, alpha, x, incx)
#define cublasDscal(handle, n, alpha, x, incx)	hcblasDscal(handle, n, alpha, x, incx)
#define cublasCscal(handle, n, alpha, x, incx)	hcblasCscal(handle, n, alpha, x, incx)
#define cublasCsscal(handle, n, alpha, x, incx)	hcblasCsscal(handle, n, alpha, x, incx)
#define cublasZscal(handle, n, alpha, x, incx)	hcblasZscal(handle, n, alpha, x, incx)
#define cublasZdscal(handle, n, alpha, x, incx)	hcblasZdscal(handle, n, alpha, x, incx)

/**
 * This function finds the (smallest) index of the element of the maximum
 * magnitude.
 */
#define cublasIsamax(handle, n, x, incx, presult)	hcblasIsamax(handle, n, x, incx, presult)
#define cublasIdamax(handle, n, x, incx, presult)	hcblasIdamax(handle, n, x, incx, presult)
#define cublasIcamax(handle, n, x, incx, presult)	hcblasIcamax(handle, n, x, incx, presult)
#define cublasIzamax(handle, n, x, incx, presult)	hcblasIzamax(handle, n, x, incx, presult)

/**
 * This function finds the (smallest) index of the element of the minimum
 * magnitude.
 */
#define cublasIsamin(handle, n, x, incx, presult)	hcblasIsamin(handle, n, x, incx, presult)
#define cublasIdamin(handle, n, x, incx, presult)	hcblasIdamin(handle, n, x, incx, presult)
#define cublasIcamin(handle, n, x, incx, presult)	hcblasIcamin(handle, n, x, incx, presult)
#define cublasIzamin(handle, n, x, incx, presult)	hcblasIzamin(handle, n, x, incx, presult)

/**
 * This function computes the sum of the absolute values of the elements of
 * vector x.
 */
#define cublasSasum(handle, n, x, incx, presult)	hcblasSasum(handle, n, x, incx, presult)
#define cublasDasum(handle, n, x, incx, presult)	hcblasDasum(handle, n, x, incx, presult)
#define cublasScasum(handle, n, x, incx, presult)	hcblasScasum(handle, n, x, incx, presult)
#define cublasDzasum(handle, n, x, incx, presult)	hcblasDzasum(handle, n, x, incx, presult)

/**
 * cublasComputeType_t enumerate type is used in cublasGemmEx() and
 * cublasLtMatmul() (including all batched and strided batched variants) to
 * choose compute precision modes as defined below.
 */
#define cublasComputeType_t	hcblasComputeType_t
#define CUBLAS_COMPUTE_16F	HCBLAS_COMPUTE_16F
#define CUBLAS_COMPUTE_16F_PEDANTIC	HCBLAS_COMPUTE_16F_PEDANTIC
#define CUBLAS_COMPUTE_32F	HCBLAS_COMPUTE_32F
#define CUBLAS_COMPUTE_32F_PEDANTIC	HCBLAS_COMPUTE_32F_PEDANTIC
#define CUBLAS_COMPUTE_32F_FAST_16F	HCBLAS_COMPUTE_32F_FAST_16F
#define CUBLAS_COMPUTE_32F_FAST_16BF	HCBLAS_COMPUTE_32F_FAST_16BF
#define CUBLAS_COMPUTE_32F_FAST_TF32	HCBLAS_COMPUTE_32F_FAST_TF32
#define CUBLAS_COMPUTE_32F_EMULATED_16BFX9	HCBLAS_COMPUTE_32F_EMULATED_16BFX9
#define CUBLAS_COMPUTE_64F	HCBLAS_COMPUTE_64F
#define CUBLAS_COMPUTE_64F_PEDANTIC	HCBLAS_COMPUTE_64F_PEDANTIC
#define CUBLAS_COMPUTE_32I	HCBLAS_COMPUTE_32I
#define CUBLAS_COMPUTE_32I_PEDANTIC	HCBLAS_COMPUTE_32I_PEDANTIC

/**
 * see /usr/local/cuda-12.9/targets/x86_64-linux/include/library_types.h
 */
#define cudaDataType_t	hpccDataType_t
#define CUDA_R_16F	HPCC_R_16F
#define CUDA_C_16F	HPCC_C_16F
#define CUDA_R_16BF	HPCC_R_16BF
#define CUDA_C_16BF	HPCC_C_16BF
#define CUDA_R_32F	HPCC_R_32F
#define CUDA_C_32F	HPCC_C_32F
#define CUDA_R_64F	HPCC_R_64F
#define CUDA_C_64F	HPCC_C_64F
#define CUDA_R_4I	HPCC_R_4I
#define CUDA_C_4I	HPCC_C_4I
#define CUDA_R_4U	HPCC_R_4U
#define CUDA_C_4U	HPCC_C_4U
#define CUDA_R_8I	HPCC_R_8I
#define CUDA_C_8I	HPCC_C_8I
#define CUDA_R_8U	HPCC_R_8U
#define CUDA_C_8U	HPCC_C_8U
#define CUDA_R_16I	HPCC_R_16I
#define CUDA_C_16I	HPCC_C_16I
#define CUDA_R_16U	HPCC_R_16U
#define CUDA_C_16U	HPCC_C_16U
#define CUDA_R_32I	HPCC_R_32I
#define CUDA_C_32I	HPCC_C_32I
#define CUDA_R_32U	HPCC_R_32U
#define CUDA_C_32U	HPCC_C_32U
#define CUDA_R_64I	HPCC_R_64I
#define CUDA_C_64I	HPCC_C_64I
#define CUDA_R_64U	HPCC_R_64U
#define CUDA_C_64U	HPCC_C_64U
#define CUDA_R_8F_E4M3	HPCC_R_8F_E4M3
#define CUDA_R_8F_UE4M3	HPCC_R_8F_UE4M3
#define CUDA_R_8F_E5M2	HPCC_R_8F_E5M2
#define CUDA_R_8F_UE8M0	HPCC_R_8F_UE8M0
#define CUDA_R_6F_E2M3	HPCC_R_6F_E2M3
#define CUDA_R_6F_E3M2	HPCC_R_6F_E3M2
#define CUDA_R_4F_E2M1	HPCC_R_4F_E2M1

/**
 * float - s, S, real single-precision
 * double - d, D, real double-precision
 * cuComplex - c, C, complex single-precision
 * cuDoubleComplex - z, Z, complex double-precision
 */
#define cuComplex	hcComplex
#define cuDoubleComplex	hcDoubleComplex
