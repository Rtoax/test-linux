// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
/******************************************************************************\
 * BLAS: Basic Linear Algebra Subprograms
 * see /usr/local/cuda-12.9/targets/x86_64-linux/include/cublas_api.h
 *
 * refs:
 * - https://docs.nvidia.com/cuda/cublas/index.html
\******************************************************************************/
/**
 * Input definitions:
 * - __USE_HIP__	AMD ROCm HIP
 * - __USE_HPCC__	Mars
 * - __USE_LUCA__	Luca
 */
#ifndef __CUDA_ADAPTER_CUBLAS_H
#define __CUDA_ADAPTER_CUBLAS_H 1

#ifdef CUBLAS_H_
#error "CudaAdapter not allow include origin CUDA cublas.h"
#endif

#include "wrapper_defs.h"
#include "cublas_api.h"

/* cublasStatus cublasInit(void); */
#define cublasInit cuX(blasInit)
/* cublasStatus cublasShutdown(void); */
#define cublasShutdown cuX(blasShutdown)
/* cublasStatus cublasGetError(void); */
#define cublasGetError cuX(blasGetError)

/* cublasStatus cublasGetVersion(int* version); */
#define cublasGetVersion cuX(blasGetVersion)

/* cublasStatus cublasAlloc(int n, int elemSize, void** devicePtr); */
#define cublasAlloc cuX(blasAlloc)

/* cublasStatus cublasFree(void* devicePtr); */
#define cublasFree cuX(blasFree)

/*
 *
 * CUDA V12.2.140
 * const char* cublasGetStatusString(cublasStatus_t status);
 *
 * HIP:
 * const char* hipblasStatusToString(hipblasStatus_t status);
 */
#ifdef __USE_HIP__
#define cublasGetStatusString(status) hipblasStatusToString(status)
#else
#define cublasGetStatusString(status) cuX(blasGetStatusString(status))
#endif

#define cublasCreate(handle) cuX(blasCreate(handle))
#define cublasDestroy(handle) cuX(blasDestroy(handle))

#define cublasGetProperty(type, pvalue) cuX(blasGetProperty(type, pvalue))

#define cublasSetMatrix(rows, cols, elemsize, A, ola, B, ldb) \
 cuX(blasSetMatrix(rows, cols, elemsize, A, ola, B, ldb))
/**
 * cublasStatus_t cublasGetMatrix(int rows, int cols, int elemSize,
 *                                const void *devicePtr, int ldDevice,
 *                                void *hostPtr, int ldHost);
 */
#define cublasGetMatrix(rows, cols, elemsize, A, ola, B, ldb) \
 cuX(blasGetMatrix(rows, cols, elemsize, A, ola, B, ldb))

#define cublasSetVector(n, elemSize, x, incx, y, incy) \
 cuX(blasSetVector(n, elemSize, x, incx, y, incy))
#define cublasGetVector(n, elemSize, x, incx, y, incy) \
 cuX(blasGetVector(n, elemSize, x, incx, y, incy))

#define cublasGetPointerMode(handle, mode) cuX(blasGetPointerMode(handle, mode))
#define cublasSetPointerMode(handle, mode) cuX(blasSetPointerMode(handle, mode))

/**
 * x[j] = alpha * x[j]
 * i = 1 ... n
 * j = 1 + (i − 1) * incx
 *
 * S-float, D-double, C-Complex, Cs-Complex/float, Z-DoubleComplex, Zd-DoubleComplex/double
 */
#define cublasSscal(handle, n, alpha, x, incx) cuX(blasSscal(handle, n, alpha, x, incx))
#define cublasDscal(handle, n, alpha, x, incx) cuX(blasDscal(handle, n, alpha, x, incx))
#define cublasCscal(handle, n, alpha, x, incx) cuX(blasCscal(handle, n, alpha, x, incx))
#define cublasCsscal(handle, n, alpha, x, incx) cuX(blasCsscal(handle, n, alpha, x, incx))
#define cublasZscal(handle, n, alpha, x, incx) cuX(blasZscal(handle, n, alpha, x, incx))
#define cublasZdscal(handle, n, alpha, x, incx) cuX(blasZdscal(handle, n, alpha, x, incx))

/**
 * This function finds the (smallest) index of the element of the maximum
 * magnitude.
 */
#define cublasIsamax(handle, n, x, incx, presult) cuX(blasIsamax(handle, n, x, incx, presult))
#define cublasIdamax(handle, n, x, incx, presult) cuX(blasIdamax(handle, n, x, incx, presult))
#define cublasIcamax(handle, n, x, incx, presult) cuX(blasIcamax(handle, n, x, incx, presult))
#define cublasIzamax(handle, n, x, incx, presult) cuX(blasIzamax(handle, n, x, incx, presult))

/**
 * This function finds the (smallest) index of the element of the minimum
 * magnitude.
 */
#define cublasIsamin(handle, n, x, incx, presult) cuX(blasIsamin(handle, n, x, incx, presult))
#define cublasIdamin(handle, n, x, incx, presult) cuX(blasIdamin(handle, n, x, incx, presult))
#define cublasIcamin(handle, n, x, incx, presult) cuX(blasIcamin(handle, n, x, incx, presult))
#define cublasIzamin(handle, n, x, incx, presult) cuX(blasIzamin(handle, n, x, incx, presult))

/**
 * This function computes the sum of the absolute values of the elements of
 * vector x.
 */
#define cublasSasum(handle, n, x, incx, presult) cuX(blasSasum(handle, n, x, incx, presult))
#define cublasDasum(handle, n, x, incx, presult) cuX(blasDasum(handle, n, x, incx, presult))
#define cublasScasum(handle, n, x, incx, presult) cuX(blasScasum(handle, n, x, incx, presult))
#define cublasDzasum(handle, n, x, incx, presult) cuX(blasDzasum(handle, n, x, incx, presult))

/**
 * This function multiplies the vector x by the scalar alpha and adds it to
 * the vector y overwriting the latest vector with the result.
 *
 * y[j] = alpha x x[k] + y[j]
 * i = 1, ..., n
 * k = 1 + (i − 1) * incx
 * j = 1 + (i − 1) * incy
 */
#define cublasSaxpy(handle, n, alpha, x, incx, y, incy) cuX(blasSaxpy(handle, n, alpha, x, incx, y, incy))
#define cublasDaxpy(handle, n, alpha, x, incx, y, incy) cuX(blasDaxpy(handle, n, alpha, x, incx, y, incy))
#define cublasCaxpy(handle, n, alpha, x, incx, y, incy) cuX(blasCaxpy(handle, n, alpha, x, incx, y, incy))
#define cublasZaxpy(handle, n, alpha, x, incx, y, incy) cuX(blasZaxpy(handle, n, alpha, x, incx, y, incy))

/**
 * This function copies the vector x into the vector y.
 *
 * y[j] = x[k]
 * i = 1, ..., n
 * k = 1 + (i − 1) * incx
 * j = 1 + (i − 1) * incy
 */
#define cublasScopy(handle, n, x, incx, y, incy) cuX(blasScopy(handle, n, x, incx, y, incy))
#define cublasDcopy(handle, n, x, incx, y, incy) cuX(blasDcopy(handle, n, x, incx, y, incy))
#define cublasCcopy(handle, n, x, incx, y, incy) cuX(blasCcopy(handle, n, x, incx, y, incy))
#define cublasZcopy(handle, n, x, incx, y, incy) cuX(blasZcopy(handle, n, x, incx, y, incy))

/**
 * This function computes the dot product of vectors x and y.
 */
#define cublasSdot(handle, n, x, incx, y, incy, presult) cuX(blasSdot(handle, n, x, incx, y, incy, presult))
#define cublasDdot(handle, n, x, incx, y, incy, presult) cuX(blasDdot(handle, n, x, incx, y, incy, presult))
#define cublasCdotu(handle, n, x, incx, y, incy, presult) cuX(blasCdotu(handle, n, x, incx, y, incy, presult))
#define cublasCdotc(handle, n, x, incx, y, incy, presult) cuX(blasCdotc(handle, n, x, incx, y, incy, presult))
#define cublasZdotu(handle, n, x, incx, y, incy, presult) cuX(blasZdotu(handle, n, x, incx, y, incy, presult))
#define cublasZdotc(handle, n, x, incx, y, incy, presult) cuX(blasZdotc(handle, n, x, incx, y, incy, presult))

/**
 * This function computes the Euclidean norm of the vector x.
 */
#define cublasSnrm2(handle, n, x, incx, presult) cuX(blasSnrm2(handle, n, x, incx, presult))
#define cublasDnrm2(handle, n, x, incx, presult) cuX(blasDnrm2(handle, n, x, incx, presult))
#define cublasScnrm2(handle, n, x, incx, presult) cuX(blasScnrm2(handle, n, x, incx, presult))
#define cublasDznrm2(handle, n, x, incx, presult) cuX(blasDznrm2(handle, n, x, incx, presult))

/**
 * This function applies Givens rotation matrix.
 */
#define cublasSrot(handle, n, x, incx, y, incy, c, s) cuX(blasSrot(handle, n, x, incx, y, incy, c, s))
#define cublasDrot(handle, n, x, incx, y, incy, c, s) cuX(blasDrot(handle, n, x, incx, y, incy, c, s))
#define cublasCrot(handle, n, x, incx, y, incy, c, s) cuX(blasCrot(handle, n, x, incx, y, incy, c, s))
#define cublasCsrot(handle, n, x, incx, y, incy, c, s) cuX(blasCsrot(handle, n, x, incx, y, incy, c, s))
#define cublasZrot(handle, n, x, incx, y, incy, c, s) cuX(blasZrot(handle, n, x, incx, y, incy, c, s))
#define cublasZdrot(handle, n, x, incx, y, incy, c, s) cuX(blasZdrot(handle, n, x, incx, y, incy, c, s))

/**
 * This function constructs the Givens rotation matrix.
 */
#define cublasSrotg(handle, a, b, c, s) cuX(blasSrotg(handle, a, b, c, s))
#define cublasDrotg(handle, a, b, c, s) cuX(blasDrotg(handle, a, b, c, s))
#define cublasCrotg(handle, a, b, c, s) cuX(blasCrotg(handle, a, b, c, s))
#define cublasZrotg(handle, a, b, c, s) cuX(blasZrotg(handle, a, b, c, s))

#define cublasSrotm(handle, n, x, incx, y, incy, param) cuX(blasSrotm(handle, n, x, incx, y, incy, param))
#define cublasDrotm(handle, n, x, incx, y, incy, param) cuX(blasDrotm(handle, n, x, incx, y, incy, param))

/**
 * This function performs the matrix-matrix multiplication.
 *
 * C = alpha op(A) op(B) + beta C
 */
/**
 * CUDA:
 * cublasStatus_t cublasSgemm(cublasHandle_t handle,
 *                          cublasOperation_t transa, cublasOperation_t transb,
 *                          int m, int n, int k,
 *                          const float           *alpha,
 *                          const float           *A, int lda,
 *                          const float           *B, int ldb,
 *                          const float           *beta,
 *                          float           *C, int ldc)
 * HIP:
 * hipblasStatus_t hipblasSgemm(hipblasHandle_t    handle,
 *                              hipblasOperation_t transA,
 *                              hipblasOperation_t transB,
 *                              int                m,
 *                              int                n,
 *                              int                k,
 *                              const float*       alpha,
 *                              const float*       AP,
 *                              int                lda,
 *                              const float*       BP,
 *                              int                ldb,
 *                              const float*       beta,
 *                              float*             CP,
 *                              int                ldc);
 */
#define cublasSgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
 cuX(blasSgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasDgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
 cuX(blasDgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasCgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
 cuX(blasCgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasZgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
 cuX(blasZgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
/**
 * CUDA:
 * cublasStatus_t cublasHgemm(cublasHandle_t handle,
 *                            cublasOperation_t transa,
 *                            cublasOperation_t transb,
 *                            int m,
 *                            int n,
 *                            int k,
 *                            const __half* alpha,
 *                            const __half* A,
 *                            int lda,
 *                            const __half* B,
 *                            int ldb,
 *                            const __half* beta,
 *                            __half* C,
 *                            int ldc);
 *
 * HIP:
 * hipblasStatus_t hipblasHgemm(hipblasHandle_t    handle,
 *                              hipblasOperation_t transA,
 *                              hipblasOperation_t transB,
 *                              int                m,
 *                              int                n,
 *                              int                k,
 *                              const hipblasHalf* alpha,
 *                              const hipblasHalf* AP,
 *                              int                lda,
 *                              const hipblasHalf* BP,
 *                              int                ldb,
 *                              const hipblasHalf* beta,
 *                              hipblasHalf*       CP,
 *                              int                ldc);
 */
#define cublasHgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
 cuX(blasHgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))

#define cublasDgemv(handle, transa, m, n, alpha, a, lda, x, incx, beta, y, incy) \
 cuX(blasDgemv(handle, transa, m, n, alpha, a, lda, x, incx, beta, y, incy))

/**
 * CUDA:
 * cublasStatus_t cublasGemmEx(cublasHandle_t handle,
 *                          cublasOperation_t transa,
 *                          cublasOperation_t transb,
 *                          int m,
 *                          int n,
 *                          int k,
 *                          const void    *alpha,
 *                          const void     *A,
 *                          cudaDataType_t Atype,
 *                          int lda,
 *                          const void     *B,
 *                          cudaDataType_t Btype,
 *                          int ldb,
 *                          const void    *beta,
 *                          void           *C,
 *                          cudaDataType_t Ctype,
 *                          int ldc,
 *                          cublasComputeType_t computeType,
 *                          cublasGemmAlgo_t algo)
 *
 * HIP:
 * hipblasStatus_t hipblasGemmEx(hipblasHandle_t    handle,
 *                               hipblasOperation_t transA,
 *                               hipblasOperation_t transB,
 *                               int                m,
 *                               int                n,
 *                               int                k,
 *                               const void*        alpha,
 *                               const void*        A,
 *                               hipblasDatatype_t  aType,
 *                               int                lda,
 *                               const void*        B,
 *                               hipblasDatatype_t  bType,
 *                               int                ldb,
 *                               const void*        beta,
 *                               void*              C,
 *                               hipblasDatatype_t  cType,
 *                               int                ldc,
 *                               hipblasDatatype_t  computeType,
 *                               hipblasGemmAlgo_t  algo);
 */
#define cublasGemmEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, \
       B, Btype, ldb, beta, C, Ctype, ldc, computeType, algo) \
 cuX(blasGemmEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, \
       B, Btype, ldb, beta, C, Ctype, ldc, computeType, algo))
/**
 * HIP:
 * hipblasStatus_t hipblasGemmEx_v2(hipblasHandle_t      handle,
 *                                  hipblasOperation_t   transA,
 *                                  hipblasOperation_t   transB,
 *                                  int                  m,
 *                                  int                  n,
 *                                  int                  k,
 *                                  const void*          alpha,
 *                                  const void*          A,
 *                                  hipDataType          aType,
 *                                  int                  lda,
 *                                  const void*          B,
 *                                  hipDataType          bType,
 *                                  int                  ldb,
 *                                  const void*          beta,
 *                                  void*                C,
 *                                  hipDataType          cType,
 *                                  int                  ldc,
 *                                  hipblasComputeType_t computeType,
 *                                  hipblasGemmAlgo_t    algo);
 */
#define cublasGemmEx_v2 cuX(blasGemmEx_v2)

/**
 * cublasStatus_t cublasSgemmEx(cublasHandle_t handle,
 *                          cublasOperation_t transa,
 *                          cublasOperation_t transb,
 *                          int m,
 *                          int n,
 *                          int k,
 *                          const float    *alpha,
 *                          const void     *A,
 *                          cudaDataType_t Atype,
 *                          int lda,
 *                          const void     *B,
 *                          cudaDataType_t Btype,
 *                          int ldb,
 *                          const float    *beta,
 *                          void           *C,
 *                          cudaDataType_t Ctype,
 *                          int ldc)
 */
#define cublasSgemmEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, \
        B, Btype, ldb, beta, C, Ctype, ldc) \
 cuX(blasSgemmEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, \
        B, Btype, ldb, beta, C, Ctype, ldc))

#if defined(__USE_HPCC__)
/**
 * see /usr/local/cuda-12.9/targets/x86_64-linux/include/library_types.h
 */
#define cudaDataType_t hpccDataType_t
#define cudaDataType hpccDataType
/* The data type is a 16-bit real half precision floating-point */
#define CUDA_R_16F HPCC_R_16F
/* The data type is a 32-bit structure comprised of two half precision
 * floating-points representing a complex number. */
#define CUDA_C_16F HPCC_C_16F
/* The data type is a 16-bit real bfloat16 floating-point */
#define CUDA_R_16BF HPCC_R_16BF
#define CUDA_C_16BF HPCC_C_16BF
#define CUDA_R_32F HPCC_R_32F
#define CUDA_C_32F HPCC_C_32F
#define CUDA_R_64F HPCC_R_64F
#define CUDA_C_64F HPCC_C_64F
/* The data type is a 8-bit real signed integer */
#define CUDA_R_4I HPCC_R_4I
#define CUDA_C_4I HPCC_C_4I
#define CUDA_R_4U HPCC_R_4U
#define CUDA_C_4U HPCC_C_4U
#define CUDA_R_8I HPCC_R_8I
#define CUDA_C_8I HPCC_C_8I
#define CUDA_R_8U HPCC_R_8U
#define CUDA_C_8U HPCC_C_8U
#define CUDA_R_16I HPCC_R_16I
#define CUDA_C_16I HPCC_C_16I
#define CUDA_R_16U HPCC_R_16U
#define CUDA_C_16U HPCC_C_16U
#define CUDA_R_32I HPCC_R_32I
#define CUDA_C_32I HPCC_C_32I
#define CUDA_R_32U HPCC_R_32U
#define CUDA_C_32U HPCC_C_32U
#define CUDA_R_64I HPCC_R_64I
#define CUDA_C_64I HPCC_C_64I
#define CUDA_R_64U HPCC_R_64U
#define CUDA_C_64U HPCC_C_64U
#define CUDA_R_8F_E4M3 HPCC_R_8F_E4M3
#define CUDA_R_8F_UE4M3 HPCC_R_8F_UE4M3
#define CUDA_R_8F_E5M2 HPCC_R_8F_E5M2
#define CUDA_R_8F_UE8M0 HPCC_R_8F_UE8M0
#define CUDA_R_6F_E2M3 HPCC_R_6F_E2M3
#define CUDA_R_6F_E3M2 HPCC_R_6F_E3M12
#define CUDA_R_4F_E2M1 HPCC_R_4F_E2M1
#elif defined(__USE_LUCA__)
#define cudaDataType_t lucaDataType_t
#define cudaDataType lucaDataType
/* The data type is a 16-bit real half precision floating-point */
#define CUDA_R_16F LUCA_R_16F
/* The data type is a 32-bit structure comprised of two half precision
 * floating-points representing a complex number. */
#define CUDA_C_16F LUCA_C_16F
/* The data type is a 16-bit real bfloat16 floating-point */
#define CUDA_R_16BF LUCA_R_16BF
#define CUDA_C_16BF LUCA_C_16BF
#define CUDA_R_32F LUCA_R_32F
#define CUDA_C_32F LUCA_C_32F
#define CUDA_R_64F LUCA_R_64F
#define CUDA_C_64F LUCA_C_64F
/* The data type is a 8-bit real signed integer */
#define CUDA_R_4I LUCA_R_4I
#define CUDA_C_4I LUCA_C_4I
#define CUDA_R_4U LUCA_R_4U
#define CUDA_C_4U LUCA_C_4U
#define CUDA_R_8I LUCA_R_8I
#define CUDA_C_8I LUCA_C_8I
#define CUDA_R_8U LUCA_R_8U
#define CUDA_C_8U LUCA_C_8U
#define CUDA_R_16I LUCA_R_16I
#define CUDA_C_16I LUCA_C_16I
#define CUDA_R_16U LUCA_R_16U
#define CUDA_C_16U LUCA_C_16U
#define CUDA_R_32I LUCA_R_32I
#define CUDA_C_32I LUCA_C_32I
#define CUDA_R_32U LUCA_R_32U
#define CUDA_C_32U LUCA_C_32U
#define CUDA_R_64I LUCA_R_64I
#define CUDA_C_64I LUCA_C_64I
#define CUDA_R_64U LUCA_R_64U
#define CUDA_C_64U LUCA_C_64U
#define CUDA_R_8F_E4M3 LUCA_R_8F_E4M3
#define CUDA_R_8F_UE4M3 LUCA_R_8F_UE4M3
#define CUDA_R_8F_E5M2 LUCA_R_8F_E5M2
#define CUDA_R_8F_UE8M0 LUCA_R_8F_UE8M0
#define CUDA_R_6F_E2M3 LUCA_R_6F_E2M3
#define CUDA_R_6F_E3M2 LUCA_R_6F_E3M12
#define CUDA_R_4F_E2M1 LUCA_R_4F_E2M1
#elif defined(__USE_HIP__)
# ifndef cudaDataType_t
#  define cudaDataType_t cudaDataType
# endif
#define cudaDataType cudaX(DataType)
#define CUDA_R_32F HIP_R_32F
#define CUDA_R_64F HIP_R_64F
#define CUDA_R_16F HIP_R_16F
#define CUDA_R_8I HIP_R_8I
#define CUDA_C_32F HIP_C_32F
#define CUDA_C_64F HIP_C_64F
#define CUDA_C_16F HIP_C_16F
#define CUDA_C_8I HIP_C_8I
#define CUDA_R_8U HIP_R_8U
#define CUDA_C_8U HIP_C_8U
#define CUDA_R_32I HIP_R_32I
#define CUDA_C_32I HIP_C_32I
#define CUDA_R_32U HIP_R_32U
#define CUDA_C_32U HIP_C_32U
#define CUDA_R_16BF HIP_R_16BF
#define CUDA_C_16BF HIP_C_16BF
#define CUDA_R_4I HIP_R_4I
#define CUDA_C_4I HIP_C_4I
#define CUDA_R_4U HIP_R_4U
#define CUDA_C_4U HIP_C_4U
#define CUDA_R_16I HIP_R_16I
#define CUDA_C_16I HIP_C_16I
#define CUDA_R_16U HIP_R_16U
#define CUDA_C_16U HIP_C_16U
#define CUDA_R_64I HIP_R_64I
#define CUDA_C_64I HIP_C_64I
#define CUDA_R_64U HIP_R_64U
#define CUDA_C_64U HIP_C_64U
#define CUDA_R_8F_E4M3 HIP_R_8F_E4M3
#define CUDA_R_8F_E5M2 HIP_R_8F_E5M2
#define CUDA_R_8F_E4M3_FNUZ HIP_R_8F_E4M3_FNUZ
#define CUDA_R_8F_E5M2_FNUZ HIP_R_8F_E5M2_FNUZ
#endif

#ifdef __USE_HPCC__
# include <hcblas/hcblas.h>
#elif defined(__USE_LUCA__)
# include <lcblas/lcblas.h>
#elif defined(__USE_HIP__)
# ifdef __USE_HIP_V2__
#  define HIPBLAS_V2
# endif
# define HIPBLAS_USE_HIP_HALF
# include <hipblas/hipblas.h>
#endif

#endif
