// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "compat.hpp"


#ifdef __cplusplus
extern "C" {
#endif

#ifdef __USE_HIP__
hipblasStatus_t hipblasLtGetVersion(hipblasLtHandle_t handle, int* version);
#else
size_t cublasLtGetVersion();
#endif
cublasStatus_t cublasLtCreate(cublasLtHandle_t *lighthandle);
cublasStatus_t cublasLtDestroy(cublasLtHandle_t lightHandle);
cublasStatus_t cublasLtMatmulDescCreate(cublasLtMatmulDesc_t *matmulDesc,
					cublasComputeType_t computeType,
					#ifdef __USE_HIP__
					hipDataType scaleType
					#else
					cudaDataType_t scaleType
					#endif
				       );

cublasStatus_t cublasLtMatmulDescDestroy(cublasLtMatmulDesc_t matmulDesc);

cublasStatus_t cublasLtMatrixLayoutCreate(cublasLtMatrixLayout_t *matLayout,
					  cudaDataType type,
					  uint64_t rows,
					  uint64_t cols,
					  int64_t ld);

cublasStatus_t cublasLtMatrixLayoutDestroy(cublasLtMatrixLayout_t matLayout);

cublasStatus_t cublasLtMatrixLayoutGetAttribute(cublasLtMatrixLayout_t matLayout,
						cublasLtMatrixLayoutAttribute_t attr,
						void* buf,
						size_t sizeInBytes,
						size_t* sizeWritten);

cublasStatus_t cublasLtMatmulPreferenceCreate(cublasLtMatmulPreference_t *pref);

cublasStatus_t cublasLtMatmulPreferenceDestroy(cublasLtMatmulPreference_t pref);

cublasStatus_t cublasLtMatmulPreferenceSetAttribute(cublasLtMatmulPreference_t pref,
						    cublasLtMatmulPreferenceAttributes_t attr,
						    const void *buf,
						    size_t sizeInBytes);

cublasStatus_t cublasLtMatmulAlgoGetHeuristic(cublasLtHandle_t lightHandle,
					      cublasLtMatmulDesc_t operationDesc,
					      cublasLtMatrixLayout_t Adesc,
					      cublasLtMatrixLayout_t Bdesc,
					      cublasLtMatrixLayout_t Cdesc,
					      cublasLtMatrixLayout_t Ddesc,
					      cublasLtMatmulPreference_t preference,
					      int requestedAlgoCount,
					      cublasLtMatmulHeuristicResult_t heuristicResultsArray[],
					      int *returnAlgoCount);

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
			      cudaStream_t stream);

#ifdef __cplusplus
}
#endif
