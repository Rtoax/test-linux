// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <cuda.h>
#include <cuda_runtime.h>
#include <cublas.h>
#include <cublasLt.h>
#include <math.h>
#include <string.h>
#include "debug.h"
#include "types.h"


#ifdef __cplusplus
extern "C" {
#endif
size_t cublasLtGetVersion(void)
{
	return 13;
}

cublasStatus_t cublasLtCreate(cublasLtHandle_t *lighthandle)
{
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasLtDestroy(cublasLtHandle_t lightHandle)
{
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasLtMatmulDescCreate(cublasLtMatmulDesc_t *matmulDesc,
					cublasComputeType_t computeType,
					cudaDataType_t scaleType)
{
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasLtMatmulDescDestroy(cublasLtMatmulDesc_t matmulDesc)
{
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasLtMatrixLayoutCreate(cublasLtMatrixLayout_t *matLayout,
					  cudaDataType type,
					  uint64_t rows,
					  uint64_t cols,
					  int64_t ld)
{
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasLtMatrixLayoutDestroy(cublasLtMatrixLayout_t matLayout)
{
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasLtMatmulPreferenceCreate(cublasLtMatmulPreference_t *pref)
{
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasLtMatmulPreferenceDestroy(cublasLtMatmulPreference_t pref)
{
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasLtMatmulPreferenceSetAttribute(cublasLtMatmulPreference_t pref,
						    cublasLtMatmulPreferenceAttributes_t attr,
						    const void *buf,
						    size_t sizeInBytes)
{
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasLtMatmulAlgoGetHeuristic(cublasLtHandle_t lightHandle,
					      cublasLtMatmulDesc_t operationDesc,
					      cublasLtMatrixLayout_t Adesc,
					      cublasLtMatrixLayout_t Bdesc,
					      cublasLtMatrixLayout_t Cdesc,
					      cublasLtMatrixLayout_t Ddesc,
					      cublasLtMatmulPreference_t preference,
					      int requestedAlgoCount,
					      cublasLtMatmulHeuristicResult_t heuristicResultsArray[],
					      int *returnAlgoCount)
{
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasLtMatmul(cublasLtHandle_t lightHandle,
			      cublasLtMatmulDesc_t computeDesc,
			      const void *alpha,
			      const void *A,
			      cublasLtMatrixLayout_t Adesc,
			      const void *B,
			      cublasLtMatrixLayout_t Bdesc,
			      const void *beta,
			      const void *C,
			      cublasLtMatrixLayout_t Cdesc,
			      void *D,
			      cublasLtMatrixLayout_t Ddesc,
			      const cublasLtMatmulAlgo_t *algo,
			      void *workspace,
			      size_t workspaceSizeInBytes,
			      cudaStream_t stream)
{
	return CUBLAS_STATUS_SUCCESS;
}
#ifdef __cplusplus
}
#endif
