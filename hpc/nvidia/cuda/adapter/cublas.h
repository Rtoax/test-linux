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

#include "wrapper_defs.h"

/* cublasStatus cublasInit(void); */
#define cublasInit __cu(blasInit)
/* cublasStatus cublasShutdown(void); */
#define cublasShutdown __cu(blasShutdown)
/* cublasStatus cublasGetError(void); */
#define cublasGetError __cu(blasGetError)

/* cublasStatus cublasGetVersion(int* version); */
#define cublasGetVersion __cu(blasGetVersion)

/* cublasStatus cublasAlloc(int n, int elemSize, void** devicePtr); */
#define cublasAlloc __cu(blasAlloc)

/* cublasStatus cublasFree(void* devicePtr); */
#define cublasFree __cu(blasFree)

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
#define cublasGetStatusString(status) __cu(blasGetStatusString(status))
#endif
#define cublasStatus_t __cu(blasStatus_t)
#define CUBLAS_STATUS_SUCCESS __CU(BLAS_STATUS_SUCCESS)
#define CUBLAS_STATUS_NOT_INITIALIZED __CU(BLAS_STATUS_NOT_INITIALIZED)
#define CUBLAS_STATUS_ALLOC_FAILED __CU(BLAS_STATUS_ALLOC_FAILED)
#define CUBLAS_STATUS_INVALID_VALUE __CU(BLAS_STATUS_INVALID_VALUE)
#define CUBLAS_STATUS_ARCH_MISMATCH __CU(BLAS_STATUS_ARCH_MISMATCH)
#define CUBLAS_STATUS_MAPPING_ERROR __CU(BLAS_STATUS_MAPPING_ERROR)
#define CUBLAS_STATUS_EXECUTION_FAILED __CU(BLAS_STATUS_EXECUTION_FAILED)
#define CUBLAS_STATUS_INTERNAL_ERROR __CU(BLAS_STATUS_INTERNAL_ERROR)
#define CUBLAS_STATUS_NOT_SUPPORTED __CU(BLAS_STATUS_NOT_SUPPORTED)

#define cublasHandle_t __cu(blasHandle_t)
#define cublasCreate(handle) __cu(blasCreate(handle))
#define cublasDestroy(handle) __cu(blasDestroy(handle))

/**
 * CUDA: size_t CUBLASWINAPI cublasLtGetVersion(void);
 * HIP: hipblasStatus_t hipblasLtGetVersion(hipblasLtHandle_t handle, int* version);
 */
#ifdef __USE_HIP__
#define cublasLtGetVersion(handle, pv) __cu(blasLtGetVersion(handle, pv))
#else
#define cublasLtGetVersion() __cu(blasLtGetVersion())
#endif
#define cublasGetProperty(type, pvalue) __cu(blasGetProperty(type, pvalue))

/**
 * The cublasOperation_t type indicates which operation needs to be performed
 * with the dense matrix.
 */
#define cublasOperation_t __cu(blasOperation_t)
/* The non-transpose operation is selected. */
#define CUBLAS_OP_N __CU(BLAS_OP_N)
/* The transpose operation is selected. */
#define CUBLAS_OP_T __CU(BLAS_OP_T)
/* The conjugate transpose operation is selected. */
#define CUBLAS_OP_C __CU(BLAS_OP_C)
#define CUBLAS_OP_HERMITAN __CU(BLAS_OP_HERMITAN)
#define CUBLAS_OP_CONJG __CU(BLAS_OP_CONJG)

#define cublasFillMode_t __cu(blasFillMode_t)
#define CUBLAS_FILL_MODE_LOWER __CU(BLAS_FILL_MODE_LOWER)
#define CUBLAS_FILL_MODE_UPPER __CU(BLAS_FILL_MODE_UPPER)
#define CUBLAS_FILL_MODE_FULL __CU(BLAS_FILL_MODE_FULL)

#define cublasSetMatrix(rows, cols, elemsize, A, ola, B, ldb) \
 __cu(blasSetMatrix(rows, cols, elemsize, A, ola, B, ldb))
/**
 * cublasStatus_t cublasGetMatrix(int rows, int cols, int elemSize,
 *                                const void *devicePtr, int ldDevice,
 *                                void *hostPtr, int ldHost);
 */
#define cublasGetMatrix(rows, cols, elemsize, A, ola, B, ldb) \
 __cu(blasGetMatrix(rows, cols, elemsize, A, ola, B, ldb))

#define cublasSetVector(n, elemSize, x, incx, y, incy) \
 __cu(blasSetVector(n, elemSize, x, incx, y, incy))
#define cublasGetVector(n, elemSize, x, incx, y, incy) \
 __cu(blasGetVector(n, elemSize, x, incx, y, incy))

/**
 * The cublasPointerMode_t type indicates whether the scalar values are passed
 * by reference on the host or device.
 */
#define cublasPointerMode_t __cu(blasPointerMode_t)
#define CUBLAS_POINTER_MODE_HOST __CU(BLAS_POINTER_MODE_HOST)
#define CUBLAS_POINTER_MODE_DEVICE __CU(BLAS_POINTER_MODE_DEVICE)

#define cublasGetPointerMode(handle, mode) __cu(blasGetPointerMode(handle, mode))
#define cublasSetPointerMode(handle, mode) __cu(blasSetPointerMode(handle, mode))

/**
 * x[j] = alpha * x[j]
 * i = 1 ... n
 * j = 1 + (i − 1) * incx
 *
 * S-float, D-double, C-Complex, Cs-Complex/float, Z-DoubleComplex, Zd-DoubleComplex/double
 */
#define cublasSscal(handle, n, alpha, x, incx) __cu(blasSscal(handle, n, alpha, x, incx))
#define cublasDscal(handle, n, alpha, x, incx) __cu(blasDscal(handle, n, alpha, x, incx))
#define cublasCscal(handle, n, alpha, x, incx) __cu(blasCscal(handle, n, alpha, x, incx))
#define cublasCsscal(handle, n, alpha, x, incx) __cu(blasCsscal(handle, n, alpha, x, incx))
#define cublasZscal(handle, n, alpha, x, incx) __cu(blasZscal(handle, n, alpha, x, incx))
#define cublasZdscal(handle, n, alpha, x, incx) __cu(blasZdscal(handle, n, alpha, x, incx))

/**
 * This function finds the (smallest) index of the element of the maximum
 * magnitude.
 */
#define cublasIsamax(handle, n, x, incx, presult) __cu(blasIsamax(handle, n, x, incx, presult))
#define cublasIdamax(handle, n, x, incx, presult) __cu(blasIdamax(handle, n, x, incx, presult))
#define cublasIcamax(handle, n, x, incx, presult) __cu(blasIcamax(handle, n, x, incx, presult))
#define cublasIzamax(handle, n, x, incx, presult) __cu(blasIzamax(handle, n, x, incx, presult))

/**
 * This function finds the (smallest) index of the element of the minimum
 * magnitude.
 */
#define cublasIsamin(handle, n, x, incx, presult) __cu(blasIsamin(handle, n, x, incx, presult))
#define cublasIdamin(handle, n, x, incx, presult) __cu(blasIdamin(handle, n, x, incx, presult))
#define cublasIcamin(handle, n, x, incx, presult) __cu(blasIcamin(handle, n, x, incx, presult))
#define cublasIzamin(handle, n, x, incx, presult) __cu(blasIzamin(handle, n, x, incx, presult))

/**
 * This function computes the sum of the absolute values of the elements of
 * vector x.
 */
#define cublasSasum(handle, n, x, incx, presult) __cu(blasSasum(handle, n, x, incx, presult))
#define cublasDasum(handle, n, x, incx, presult) __cu(blasDasum(handle, n, x, incx, presult))
#define cublasScasum(handle, n, x, incx, presult) __cu(blasScasum(handle, n, x, incx, presult))
#define cublasDzasum(handle, n, x, incx, presult) __cu(blasDzasum(handle, n, x, incx, presult))

/**
 * This function multiplies the vector x by the scalar alpha and adds it to
 * the vector y overwriting the latest vector with the result.
 *
 * y[j] = alpha x x[k] + y[j]
 * i = 1, ..., n
 * k = 1 + (i − 1) * incx
 * j = 1 + (i − 1) * incy
 */
#define cublasSaxpy(handle, n, alpha, x, incx, y, incy) __cu(blasSaxpy(handle, n, alpha, x, incx, y, incy))
#define cublasDaxpy(handle, n, alpha, x, incx, y, incy) __cu(blasDaxpy(handle, n, alpha, x, incx, y, incy))
#define cublasCaxpy(handle, n, alpha, x, incx, y, incy) __cu(blasCaxpy(handle, n, alpha, x, incx, y, incy))
#define cublasZaxpy(handle, n, alpha, x, incx, y, incy) __cu(blasZaxpy(handle, n, alpha, x, incx, y, incy))

/**
 * This function copies the vector x into the vector y.
 *
 * y[j] = x[k]
 * i = 1, ..., n
 * k = 1 + (i − 1) * incx
 * j = 1 + (i − 1) * incy
 */
#define cublasScopy(handle, n, x, incx, y, incy) __cu(blasScopy(handle, n, x, incx, y, incy))
#define cublasDcopy(handle, n, x, incx, y, incy) __cu(blasDcopy(handle, n, x, incx, y, incy))
#define cublasCcopy(handle, n, x, incx, y, incy) __cu(blasCcopy(handle, n, x, incx, y, incy))
#define cublasZcopy(handle, n, x, incx, y, incy) __cu(blasZcopy(handle, n, x, incx, y, incy))

/**
 * This function computes the dot product of vectors x and y.
 */
#define cublasSdot(handle, n, x, incx, y, incy, presult) __cu(blasSdot(handle, n, x, incx, y, incy, presult))
#define cublasDdot(handle, n, x, incx, y, incy, presult) __cu(blasDdot(handle, n, x, incx, y, incy, presult))
#define cublasCdotu(handle, n, x, incx, y, incy, presult) __cu(blasCdotu(handle, n, x, incx, y, incy, presult))
#define cublasCdotc(handle, n, x, incx, y, incy, presult) __cu(blasCdotc(handle, n, x, incx, y, incy, presult))
#define cublasZdotu(handle, n, x, incx, y, incy, presult) __cu(blasZdotu(handle, n, x, incx, y, incy, presult))
#define cublasZdotc(handle, n, x, incx, y, incy, presult) __cu(blasZdotc(handle, n, x, incx, y, incy, presult))

/**
 * This function computes the Euclidean norm of the vector x.
 */
#define cublasSnrm2(handle, n, x, incx, presult) __cu(blasSnrm2(handle, n, x, incx, presult))
#define cublasDnrm2(handle, n, x, incx, presult) __cu(blasDnrm2(handle, n, x, incx, presult))
#define cublasScnrm2(handle, n, x, incx, presult) __cu(blasScnrm2(handle, n, x, incx, presult))
#define cublasDznrm2(handle, n, x, incx, presult) __cu(blasDznrm2(handle, n, x, incx, presult))

/**
 * This function applies Givens rotation matrix.
 */
#define cublasSrot(handle, n, x, incx, y, incy, c, s) __cu(blasSrot(handle, n, x, incx, y, incy, c, s))
#define cublasDrot(handle, n, x, incx, y, incy, c, s) __cu(blasDrot(handle, n, x, incx, y, incy, c, s))
#define cublasCrot(handle, n, x, incx, y, incy, c, s) __cu(blasCrot(handle, n, x, incx, y, incy, c, s))
#define cublasCsrot(handle, n, x, incx, y, incy, c, s) __cu(blasCsrot(handle, n, x, incx, y, incy, c, s))
#define cublasZrot(handle, n, x, incx, y, incy, c, s) __cu(blasZrot(handle, n, x, incx, y, incy, c, s))
#define cublasZdrot(handle, n, x, incx, y, incy, c, s) __cu(blasZdrot(handle, n, x, incx, y, incy, c, s))

/**
 * This function constructs the Givens rotation matrix.
 */
#define cublasSrotg(handle, a, b, c, s) __cu(blasSrotg(handle, a, b, c, s))
#define cublasDrotg(handle, a, b, c, s) __cu(blasDrotg(handle, a, b, c, s))
#define cublasCrotg(handle, a, b, c, s) __cu(blasCrotg(handle, a, b, c, s))
#define cublasZrotg(handle, a, b, c, s) __cu(blasZrotg(handle, a, b, c, s))

#define cublasSrotm(handle, n, x, incx, y, incy, param) __cu(blasSrotm(handle, n, x, incx, y, incy, param))
#define cublasDrotm(handle, n, x, incx, y, incy, param) __cu(blasDrotm(handle, n, x, incx, y, incy, param))

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
 __cu(blasSgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasDgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
 __cu(blasDgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasCgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
 __cu(blasCgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
#define cublasZgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
 __cu(blasZgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))
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
 __cu(blasHgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc))

#define cublasDgemv(handle, transa, m, n, alpha, a, lda, x, incx, beta, y, incy) \
 __cu(blasDgemv(handle, transa, m, n, alpha, a, lda, x, incx, beta, y, incy))

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
 __cu(blasGemmEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, \
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
#define cublasGemmEx_v2 __cu(blasGemmEx_v2)

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
 __cu(blasSgemmEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, \
        B, Btype, ldb, beta, C, Ctype, ldc))

#define cublasLtHandle_t __cu(blasLtHandle_t)
/**
 * CUDA: cublasStatus_t cublasLtCreate(cublasLtHandle_t* lightHandle);
 * HIP: hipblasStatus_t hipblasLtCreate(hipblasLtHandle_t* handle);
 */
#define cublasLtCreate(phandle) __cu(blasLtCreate(phandle))
#define cublasLtDestroy(handle) __cu(blasLtDestroy(handle))

#define cublasLtMatmulDesc_t __cu(blasLtMatmulDesc_t)
/**
 * CUDA:
 * cublasStatus_t cublasLtMatmulDescCreate(cublasLtMatmulDesc_t *matmulDesc,
 *                                         cublasComputeType_t computeType,
 *                                         cudaDataType_t scaleType);
 *
 * HIP:
 * hipblasStatus_t hipblasLtMatmulDescCreate(hipblasLtMatmulDesc_t* matmulDesc,
 *                                           hipblasComputeType_t   computeType,
 *                                           hipDataType            scaleType);
 *
 * This function creates a matrix multiply descriptor by allocating the memory
 * needed to hold its opaque structure.
 */
#define cublasLtMatmulDescCreate(pdesc, computeType, scaleType) \
 __cu(blasLtMatmulDescCreate(pdesc, computeType, scaleType))
#define cublasLtMatmulDescDestroy(desc) __cu(blasLtMatmulDescDestroy(desc))

#define cublasLtMatmulDescAttributes_t __cu(blasLtMatmulDescAttributes_t)
#define CUBLASLT_MATMUL_DESC_COMPUTE_TYPE __CU(BLASLT_MATMUL_DESC_COMPUTE_TYPE)
#define CUBLASLT_MATMUL_DESC_SCALE_TYPE  __CU(BLASLT_MATMUL_DESC_SCALE_TYPE)
#define CUBLASLT_MATMUL_DESC_POINTER_MODE __CU(BLASLT_MATMUL_DESC_POINTER_MODE)
/* more ... */

#define cublasLtMatmulHeuristicResult_t __cu(blasLtMatmulHeuristicResult_t)

#define cublasLtMatrixLayout_t __cu(blasLtMatrixLayout_t)
/**
 * CUDA:
 * cublasStatus_t cublasLtMatrixLayoutCreate(cublasLtMatrixLayout_t* matLayout,
 *                                           cudaDataType type,
 *                                             uint64_t rows,  uint64_t cols, int64_t ld);
 *
 * HIP:
 * hipblasStatus_t hipblasLtMatrixLayoutCreate(hipblasLtMatrixLayout_t* matLayout,
 *                                             hipDataType type,
 *                                             uint64_t rows, uint64_t cols, int64_t ld);
 */
#define cublasLtMatrixLayoutCreate(playout, type, rows, cols, ld) \
 __cu(blasLtMatrixLayoutCreate(playout, type, rows, cols, ld))
#define cublasLtMatrixLayoutDestroy(layout) __cu(blasLtMatrixLayoutDestroy(layout))

#define cublasLtMatrixLayoutAttribute_t __cu(blasLtMatrixLayoutAttribute_t)

/**
 * cublasStatus_t cublasLtMatrixLayoutGetAttribute(cublasLtMatrixLayout_t matLayout,
 *                                                 cublasLtMatrixLayoutAttribute_t attr,
 *                                                 void* buf,
 *                                                 size_t sizeInBytes,
 *                                                 size_t* sizeWritten);
 */
#define cublasLtMatrixLayoutGetAttribute(matLayout, attr, buf, sizeInBytes, sizeWritten) \
 __cu(blasLtMatrixLayoutGetAttribute(matLayout, attr, buf, sizeInBytes, sizeWritten))

#define CUBLASLT_MATRIX_LAYOUT_ROWS __CU(BLASLT_MATRIX_LAYOUT_ROWS)
#define CUBLASLT_MATRIX_LAYOUT_COLS __CU(BLASLT_MATRIX_LAYOUT_COLS)
#define CUBLASLT_MATRIX_LAYOUT_LD __CU(BLASLT_MATRIX_LAYOUT_LD)
#define CUBLASLT_MATRIX_LAYOUT_TYPE __CU(BLASLT_MATRIX_LAYOUT_TYPE)

#define cublasLtMatmulAlgo_t __cu(blasLtMatmulAlgo_t)
#define CUBLASLT_ALGO_CAP_SPLITK_SUPPORT __CU(BLASLT_ALGO_CAP_SPLITK_SUPPORT)
#define CUBLASLT_ALGO_CAP_REDUCTION_SCHEME_MASK __CU(BLASLT_ALGO_CAP_REDUCTION_SCHEME_MASK)
#define CUBLASLT_ALGO_CAP_CTA_SWIZZLING_SUPPORT __CU(BLASLT_ALGO_CAP_CTA_SWIZZLING_SUPPORT)
#define CUBLASLT_ALGO_CAP_STRIDED_BATCH_SUPPORT __CU(BLASLT_ALGO_CAP_STRIDED_BATCH_SUPPORT)
#define CUBLASLT_ALGO_CAP_OUT_OF_PLACE_RESULT_SUPPORT __CU(BLASLT_ALGO_CAP_OUT_OF_PLACE_RESULT_SUPPORT)
#define CUBLASLT_ALGO_CAP_UPLO_SUPPORT __CU(BLASLT_ALGO_CAP_UPLO_SUPPORT)
#define CUBLASLT_ALGO_CAP_TILE_IDS __CU(BLASLT_ALGO_CAP_TILE_IDS)
#define CUBLASLT_ALGO_CAP_CUSTOM_OPTION_MAX __CU(BLASLT_ALGO_CAP_CUSTOM_OPTION_MAX)
#define CUBLASLT_ALGO_CAP_CUSTOM_MEMORY_ORDER __CU(BLASLT_ALGO_CAP_CUSTOM_MEMORY_ORDER)
#define CUBLASLT_ALGO_CAP_POINTER_MODE_MASK __CU(BLASLT_ALGO_CAP_POINTER_MODE_MASK)
#define CUBLASLT_ALGO_CAP_EPILOGUE_MASK __CU(BLASLT_ALGO_CAP_EPILOGUE_MASK)
#define CUBLASLT_ALGO_CAP_STAGES_IDS __CU(BLASLT_ALGO_CAP_STAGES_IDS)
#define CUBLASLT_ALGO_CAP_LD_NEGATIVE __CU(BLASLT_ALGO_CAP_LD_NEGATIVE)
#define CUBLASLT_ALGO_CAP_NUMERICAL_IMPL_FLAGS __CU(BLASLT_ALGO_CAP_NUMERICAL_IMPL_FLAGS)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_A_BYTES __CU(BLASLT_ALGO_CAP_MIN_ALIGNMENT_A_BYTES)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_B_BYTES __CU(BLASLT_ALGO_CAP_MIN_ALIGNMENT_B_BYTES)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_C_BYTES __CU(BLASLT_ALGO_CAP_MIN_ALIGNMENT_C_BYTES)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_D_BYTES __CU(BLASLT_ALGO_CAP_MIN_ALIGNMENT_D_BYTES)
#define CUBLASLT_ALGO_CAP_ATOMIC_SYNC __CU(BLASLT_ALGO_CAP_ATOMIC_SYNC)

/**
 * CUDA:
 * cublasStatus_t cublasLtMatmulAlgoGetHeuristic(cublasLtHandle_t lightHandle,
 *                                               cublasLtMatmulDesc_t operationDesc,
 *                                               cublasLtMatrixLayout_t Adesc,
 *                                               cublasLtMatrixLayout_t Bdesc,
 *                                               cublasLtMatrixLayout_t Cdesc,
 *                                               cublasLtMatrixLayout_t Ddesc,
 *                                               cublasLtMatmulPreference_t preference,
 *                                               int requestedAlgoCount,
 *                                               cublasLtMatmulHeuristicResult_t heuristicResultsArray[],
 *                                               int* returnAlgoCount);
 *
 * HIP:
 * hipblasStatus_t hipblasLtMatmulAlgoGetHeuristic(hipblasLtHandle_t                handle,
 *                                                 hipblasLtMatmulDesc_t            matmulDesc,
 *                                                 hipblasLtMatrixLayout_t          Adesc,
 *                                                 hipblasLtMatrixLayout_t          Bdesc,
 *                                                 hipblasLtMatrixLayout_t          Cdesc,
 *                                                 hipblasLtMatrixLayout_t          Ddesc,
 *                                                 hipblasLtMatmulPreference_t      pref,
 *                                                 int                              requestedAlgoCount,
 *                                                 hipblasLtMatmulHeuristicResult_t heuristicResultsArray[],
 *                                                 int*                             returnAlgoCount);
 */
#define cublasLtMatmulAlgoGetHeuristic(ltHandle, matmulDesc, layoutA, layoutB, \
           layoutC, layoutD, pref, n, heuristic_result, rslt) \
 __cu(blasLtMatmulAlgoGetHeuristic(ltHandle, matmulDesc, layoutA, layoutB, \
           layoutC, layoutD, pref, n, heuristic_result, rslt))
#define cublasLtMatmulPreferenceDestroy(pref) __cu(blasLtMatmulPreferenceDestroy(pref))

#define cublasLtMatmulPreference_t __cu(blasLtMatmulPreference_t)
#define cublasLtMatmulPreferenceCreate(preference) __cu(blasLtMatmulPreferenceCreate(preference))

#define cublasLtMatmulPreferenceAttributes_t __cu(blasLtMatmulPreferenceAttributes_t)
#define cublasLtMatmulPreferenceSetAttribute(pref, arg1, ptr, size) \
 __cu(blasLtMatmulPreferenceSetAttribute(pref, arg1, ptr, size))

#define CUBLASLT_MATMUL_PREF_MAX_WORKSPACE_BYTES __CU(BLASLT_MATMUL_PREF_MAX_WORKSPACE_BYTES)

/**
 * D = alpha*(A*B) + beta*(C)
 */
#define cublasLtMatmul(lightHandle, computeDesc, alpha, A, Adesc, B, Bdesc, \
         beta, C, Cdesc, D, Ddesc, algo, workspace, \
         workspaceSizeInBytes, stream) \
 __cu(blasLtMatmul(lightHandle, computeDesc, alpha, A, Adesc, B, Bdesc, \
         beta, C, Cdesc, D, Ddesc, algo, workspace, \
         workspaceSizeInBytes, stream))

/**
 * cublasGemmAlgo_t type is an enumerant to specify the algorithm for
 * matrix-matrix multiplication.
 */
#define cublasGemmAlgo_t __cu(blasGemmAlgo_t)
#define CUBLAS_GEMM_DEFAULT __CU(BLAS_GEMM_DEFAULT)
#define CUBLAS_GEMM_ALGO0 __CU(BLAS_GEMM_ALGO0)
#define CUBLAS_GEMM_ALGO1 __CU(BLAS_GEMM_ALGO1)
#define CUBLAS_GEMM_ALGO2 __CU(BLAS_GEMM_ALGO2)
#define CUBLAS_GEMM_ALGO3 __CU(BLAS_GEMM_ALGO3)
#define CUBLAS_GEMM_ALGO4 __CU(BLAS_GEMM_ALGO4)
#define CUBLAS_GEMM_ALGO5 __CU(BLAS_GEMM_ALGO5)
#define CUBLAS_GEMM_ALGO6 __CU(BLAS_GEMM_ALGO6)
#define CUBLAS_GEMM_ALGO7 __CU(BLAS_GEMM_ALGO7)
#define CUBLAS_GEMM_ALGO8 __CU(BLAS_GEMM_ALGO8)
#define CUBLAS_GEMM_ALGO9 __CU(BLAS_GEMM_ALGO9)
#define CUBLAS_GEMM_ALGO10 __CU(BLAS_GEMM_ALGO10)
#define CUBLAS_GEMM_ALGO11 __CU(BLAS_GEMM_ALGO11)
#define CUBLAS_GEMM_ALGO12 __CU(BLAS_GEMM_ALGO12)
#define CUBLAS_GEMM_ALGO13 __CU(BLAS_GEMM_ALGO13)
#define CUBLAS_GEMM_ALGO14 __CU(BLAS_GEMM_ALGO14)
#define CUBLAS_GEMM_ALGO15 __CU(BLAS_GEMM_ALGO15)
#define CUBLAS_GEMM_ALGO16 __CU(BLAS_GEMM_ALGO16)
#define CUBLAS_GEMM_ALGO17 __CU(BLAS_GEMM_ALGO17)
#define CUBLAS_GEMM_ALGO18 __CU(BLAS_GEMM_ALGO18)
#define CUBLAS_GEMM_ALGO19 __CU(BLAS_GEMM_ALGO19)
#define CUBLAS_GEMM_ALGO20 __CU(BLAS_GEMM_ALGO20)
#define CUBLAS_GEMM_ALGO21 __CU(BLAS_GEMM_ALGO21)
#define CUBLAS_GEMM_ALGO22 __CU(BLAS_GEMM_ALGO22)
#define CUBLAS_GEMM_ALGO23 __CU(BLAS_GEMM_ALGO23)
#define CUBLAS_GEMM_DEFAULT_TENSOR_OP __CU(BLAS_GEMM_DEFAULT_TENSOR_OP)
#define CUBLAS_GEMM_ALGO0_TENSOR_OP __CU(BLAS_GEMM_ALGO0_TENSOR_OP)
#define CUBLAS_GEMM_ALGO1_TENSOR_OP __CU(BLAS_GEMM_ALGO1_TENSOR_OP)
#define CUBLAS_GEMM_ALGO2_TENSOR_OP __CU(BLAS_GEMM_ALGO2_TENSOR_OP)
#define CUBLAS_GEMM_ALGO3_TENSOR_OP __CU(BLAS_GEMM_ALGO3_TENSOR_OP)
#define CUBLAS_GEMM_ALGO4_TENSOR_OP __CU(BLAS_GEMM_ALGO4_TENSOR_OP)
#define CUBLAS_GEMM_ALGO5_TENSOR_OP __CU(BLAS_GEMM_ALGO5_TENSOR_OP)
#define CUBLAS_GEMM_ALGO6_TENSOR_OP __CU(BLAS_GEMM_ALGO6_TENSOR_OP)
#define CUBLAS_GEMM_ALGO7_TENSOR_OP __CU(BLAS_GEMM_ALGO7_TENSOR_OP)
#define CUBLAS_GEMM_ALGO8_TENSOR_OP __CU(BLAS_GEMM_ALGO8_TENSOR_OP)
#define CUBLAS_GEMM_ALGO9_TENSOR_OP __CU(BLAS_GEMM_ALGO9_TENSOR_OP)
#define CUBLAS_GEMM_ALGO10_TENSOR_OP __CU(BLAS_GEMM_ALGO10_TENSOR_OP)
#define CUBLAS_GEMM_ALGO11_TENSOR_OP __CU(BLAS_GEMM_ALGO11_TENSOR_OP)
#define CUBLAS_GEMM_ALGO12_TENSOR_OP __CU(BLAS_GEMM_ALGO12_TENSOR_OP)
#define CUBLAS_GEMM_ALGO13_TENSOR_OP __CU(BLAS_GEMM_ALGO13_TENSOR_OP)
#define CUBLAS_GEMM_ALGO14_TENSOR_OP __CU(BLAS_GEMM_ALGO14_TENSOR_OP)
#define CUBLAS_GEMM_ALGO15_TENSOR_OP __CU(BLAS_GEMM_ALGO15_TENSOR_OP)
#define CUBLAS_GEMM_AUTOTUNE __CU(BLAS_GEMM_AUTOTUNE)

/**
 * cublasComputeType_t enumerate type is used in cublasGemmEx() and
 * cublasLtMatmul() (including all batched and strided batched variants) to
 * choose compute precision modes as defined below.
 */
#define cublasComputeType_t __cu(blasComputeType_t)
/**
 * This is the default and highest-performance mode for 16-bit half precision
 * floating point and all compute and intermediate storage precisions with at
 * least 16-bit half precision. Tensor Cores will be used whenever possible.
 */
#define CUBLAS_COMPUTE_16F __CU(BLAS_COMPUTE_16F)
/**
 * This mode uses 16-bit half precision floating point standardized arithmetic
 * for all phases of calculations and is primarily intended for numerical
 * robustness studies, testing, and debugging. This mode might not be as
 * performant as the other modes since it disables use of tensor cores.
 */
#define CUBLAS_COMPUTE_16F_PEDANTIC __CU(BLAS_COMPUTE_16F_PEDANTIC)
/**
 * This is the default 32-bit single precision floating point and uses compute
 * and intermediate storage precisions of at least 32-bits.
 */
#define CUBLAS_COMPUTE_32F __CU(BLAS_COMPUTE_32F)
#define CUBLAS_COMPUTE_32F_PEDANTIC __CU(BLAS_COMPUTE_32F_PEDANTIC)
/**
 * Allows the library to use Tensor Cores with automatic down-conversion and
 * 16-bit half-precision compute for 32-bit input and output matrices.
 */
#define CUBLAS_COMPUTE_32F_FAST_16F __CU(BLAS_COMPUTE_32F_FAST_16F)
#define CUBLAS_COMPUTE_32F_FAST_16BF __CU(BLAS_COMPUTE_32F_FAST_16BF)
#define CUBLAS_COMPUTE_32F_FAST_TF32 __CU(BLAS_COMPUTE_32F_FAST_TF32)
#define CUBLAS_COMPUTE_32F_EMULATED_16BFX9 __CU(BLAS_COMPUTE_32F_EMULATED_16BFX9)
/**
 * This is the default 64-bit double precision floating point and uses compute
 * and intermediate storage precisions of at least 64-bits.
 */
#define CUBLAS_COMPUTE_64F __CU(BLAS_COMPUTE_64F)
#define CUBLAS_COMPUTE_64F_PEDANTIC __CU(BLAS_COMPUTE_64F_PEDANTIC)
/**
 * This is the default 32-bit integer mode and uses compute and intermediate
 * storage precisions of at least 32-bits.
 */
#define CUBLAS_COMPUTE_32I __CU(BLAS_COMPUTE_32I)
#define CUBLAS_COMPUTE_32I_PEDANTIC __CU(BLAS_COMPUTE_32I_PEDANTIC)

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
#define cudaDataType __cuda(DataType)
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

#endif
