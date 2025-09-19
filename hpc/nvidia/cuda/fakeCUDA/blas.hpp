// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * https://docs.nvidia.com/cuda/cublas/
 */
#include "compat.hpp"
#include "types.h"

#if defined(HAVE_HPCC) && defined(__USE_HPCC__)
#define cublasGetVersion_v2	hcblasGetVersion
#define cublasCreate_v2	hcblasCreate
#define cublasDestroy_v2	hcblasDestroy
#define cublasIsamax_v2	hcblasIsamax
#define cublasIdamax_v2	hcblasIdamax
#define cublasIsamin_v2	hcblasIsamin
#define cublasIdamin_v2	hcblasIdamin
#define cublasSasum_v2	hcblasSasum
#define cublasDasum_v2	hcblasDasum
#define cublasSscal_v2	hcblasSscal
#define cublasDscal_v2	hcblasDscal
#define cublasSaxpy_v2	hcblasSaxpy
#define cublasDaxpy_v2	hcblasDaxpy
#define cublasScopy_v2	hcblasScopy
#define cublasDcopy_v2	hcblasDcopy
#define cublasSdot_v2	hcblasSdot
#define cublasDdot_v2	hcblasDdot
#define cublasSnrm2_v2	hcblasSnrm2
#define cublasDnrm2_v2	hcblasDnrm2
#define cublasSgemm_v2	hcblasSgemm
#define cublasDgemm_v2	hcblasDgemm
#endif

#ifdef __cplusplus
extern "C" {
#endif

cublasStatus_t cublasGetVersion_v2(cublasHandle_t handle, int *version);

cublasStatus_t cublasCreate_v2(cublasHandle_t *handle);

cublasStatus_t cublasDestroy_v2(cublasHandle_t handle);

cublasStatus_t cublasGetProperty(libraryPropertyType type, int *value);

cublasStatus_t cublasSetMatrix(int rows, int cols, int elemSize,
			       const void *A, int lda, void *B, int ldb);

cublasStatus_t cublasGetMatrix(int rows, int cols, int elemSize,
			       const void *A, int lda, void *B, int ldb);

cublasStatus_t cublasIsamax_v2(cublasHandle_t handle, int n,
			       const float *x, int incx, int *result);

cublasStatus_t cublasIdamax_v2(cublasHandle_t handle, int n,
			       const double *x, int incx, int *result);

cublasStatus_t cublasIsamin_v2(cublasHandle_t handle, int n,
			       const float *x, int incx, int *result);

cublasStatus_t cublasIdamin_v2(cublasHandle_t handle, int n,
			       const double *x, int incx, int *result);

cublasStatus_t cublasSasum_v2(cublasHandle_t handle, int n,
			      const float *x, int incx, float *result);

cublasStatus_t cublasDasum_v2(cublasHandle_t handle, int n,
			      const double *x, int incx, double *result);

cublasStatus_t cublasSscal_v2(cublasHandle_t handle, int n, const float *alpha,
			   float *x, int incx);

cublasStatus_t cublasDscal_v2(cublasHandle_t handle, int n, const double *alpha,
			      double *x, int incx);

cublasStatus_t cublasSaxpy_v2(cublasHandle_t handle, int n, const float *alpha,
			      const float *x, int incx,
			      float *y, int incy);

cublasStatus_t cublasDaxpy_v2(cublasHandle_t handle, int n, const double *alpha,
			      const double *x, int incx,
			      double *y, int incy);

cublasStatus_t cublasScopy_v2(cublasHandle_t handle, int n,
			      const float *x, int incx,
			      float *y, int incy);

cublasStatus_t cublasDcopy_v2(cublasHandle_t handle, int n,
			      const double *x, int incx,
			      double *y, int incy);

cublasStatus_t cublasSdot_v2(cublasHandle_t handle, int n,
			     const float *x, int incx,
			     const float *y, int incy,
			     float *result);

cublasStatus_t cublasDdot_v2(cublasHandle_t handle, int n,
			     const double *x, int incx,
			     const double *y, int incy,
			     double *result);

cublasStatus_t cublasSnrm2_v2(cublasHandle_t handle, int n,
			      const float *x, int incx, float *result);

cublasStatus_t cublasDnrm2_v2(cublasHandle_t handle, int n,
			      const double *x, int incx, double *result);

cublasStatus_t cublasSgemm_v2(cublasHandle_t handle,
			      cublasOperation_t transa, cublasOperation_t transb,
			      int m, int n, int k,
			      const float *alpha,
			      const float *A, int lda,
			      const float *B, int ldb,
			      const float *beta,
			      float *C, int ldc);

cublasStatus_t cublasDgemm_v2(cublasHandle_t handle,
			      cublasOperation_t transa, cublasOperation_t transb,
			      int m, int n, int k,
			      const double *alpha,
			      const double *A, int lda,
			      const double *B, int ldb,
			      const double *beta,
			      double *C, int ldc);

cublasStatus_t cublasHgemm(cublasHandle_t handle,
			   cublasOperation_t transa, cublasOperation_t transb,
			   int m, int n, int k,
			   const __half *alpha,
			   const __half *A, int lda,
			   const __half *B, int ldb,
			   const __half *beta,
			   __half *C, int ldc);

cublasStatus_t cublasGemmEx(cublasHandle_t handle,
			    cublasOperation_t transa,
			    cublasOperation_t transb,
			    int m,
			    int n,
			    int k,
			    const void *alpha,
			    const void *A,
			    cudaDataType_t Atype,
			    int lda,
			    const void *B,
			    cudaDataType_t Btype,
			    int ldb,
			    const void *beta,
			    void *C,
			    cudaDataType_t Ctype,
			    int ldc,
			    cublasComputeType_t computeType,
			    cublasGemmAlgo_t algo);
#ifdef __cplusplus
}
#endif
