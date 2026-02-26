// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_CUBLASLT_H
#define __CUDA_ADAPTER_CUBLASLT_H 1

#include "wrapper_defs.h"
#include "cublas_api.h"

#define cublasLtHandle_t cuX(blasLtHandle_t)

/**
 * CUDA: size_t CUBLASWINAPI cublasLtGetVersion(void);
 * HIP: hipblasStatus_t hipblasLtGetVersion(hipblasLtHandle_t handle, int* version);
 */
#ifdef __USE_HIP__
#define cublasLtGetVersion(handle, pv) cuX(blasLtGetVersion(handle, pv))
#else
#define cublasLtGetVersion() cuX(blasLtGetVersion())
#endif

/**
 * CUDA: cublasStatus_t cublasLtCreate(cublasLtHandle_t* lightHandle);
 * HIP: hipblasStatus_t hipblasLtCreate(hipblasLtHandle_t* handle);
 */
#define cublasLtCreate(phandle) cuX(blasLtCreate(phandle))
#define cublasLtDestroy(handle) cuX(blasLtDestroy(handle))

#define cublasLtMatmulDesc_t cuX(blasLtMatmulDesc_t)

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
 cuX(blasLtMatmulDescCreate(pdesc, computeType, scaleType))
#define cublasLtMatmulDescDestroy(desc) cuX(blasLtMatmulDescDestroy(desc))

#define cublasLtMatmulDescAttributes_t cuX(blasLtMatmulDescAttributes_t)
#define CUBLASLT_MATMUL_DESC_COMPUTE_TYPE CUX(BLASLT_MATMUL_DESC_COMPUTE_TYPE)
#define CUBLASLT_MATMUL_DESC_SCALE_TYPE  CUX(BLASLT_MATMUL_DESC_SCALE_TYPE)
#define CUBLASLT_MATMUL_DESC_POINTER_MODE CUX(BLASLT_MATMUL_DESC_POINTER_MODE)
/* more ... */

#define cublasLtMatmulHeuristicResult_t cuX(blasLtMatmulHeuristicResult_t)

#define cublasLtMatrixLayout_t cuX(blasLtMatrixLayout_t)
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
 cuX(blasLtMatrixLayoutCreate(playout, type, rows, cols, ld))
#define cublasLtMatrixLayoutDestroy(layout) cuX(blasLtMatrixLayoutDestroy(layout))

#define cublasLtMatrixLayoutAttribute_t cuX(blasLtMatrixLayoutAttribute_t)

/**
 * cublasStatus_t cublasLtMatrixLayoutGetAttribute(cublasLtMatrixLayout_t matLayout,
 *                                                 cublasLtMatrixLayoutAttribute_t attr,
 *                                                 void* buf,
 *                                                 size_t sizeInBytes,
 *                                                 size_t* sizeWritten);
 */
#define cublasLtMatrixLayoutGetAttribute(matLayout, attr, buf, sizeInBytes, sizeWritten) \
 cuX(blasLtMatrixLayoutGetAttribute(matLayout, attr, buf, sizeInBytes, sizeWritten))

#define CUBLASLT_MATRIX_LAYOUT_ROWS CUX(BLASLT_MATRIX_LAYOUT_ROWS)
#define CUBLASLT_MATRIX_LAYOUT_COLS CUX(BLASLT_MATRIX_LAYOUT_COLS)
#define CUBLASLT_MATRIX_LAYOUT_LD CUX(BLASLT_MATRIX_LAYOUT_LD)
#define CUBLASLT_MATRIX_LAYOUT_TYPE CUX(BLASLT_MATRIX_LAYOUT_TYPE)

#define cublasLtMatmulAlgo_t cuX(blasLtMatmulAlgo_t)
#define CUBLASLT_ALGO_CAP_SPLITK_SUPPORT CUX(BLASLT_ALGO_CAP_SPLITK_SUPPORT)
#define CUBLASLT_ALGO_CAP_REDUCTION_SCHEME_MASK CUX(BLASLT_ALGO_CAP_REDUCTION_SCHEME_MASK)
#define CUBLASLT_ALGO_CAP_CTA_SWIZZLING_SUPPORT CUX(BLASLT_ALGO_CAP_CTA_SWIZZLING_SUPPORT)
#define CUBLASLT_ALGO_CAP_STRIDED_BATCH_SUPPORT CUX(BLASLT_ALGO_CAP_STRIDED_BATCH_SUPPORT)
#define CUBLASLT_ALGO_CAP_OUT_OF_PLACE_RESULT_SUPPORT CUX(BLASLT_ALGO_CAP_OUT_OF_PLACE_RESULT_SUPPORT)
#define CUBLASLT_ALGO_CAP_UPLO_SUPPORT CUX(BLASLT_ALGO_CAP_UPLO_SUPPORT)
#define CUBLASLT_ALGO_CAP_TILE_IDS CUX(BLASLT_ALGO_CAP_TILE_IDS)
#define CUBLASLT_ALGO_CAP_CUSTOM_OPTION_MAX CUX(BLASLT_ALGO_CAP_CUSTOM_OPTION_MAX)
#define CUBLASLT_ALGO_CAP_CUSTOM_MEMORY_ORDER CUX(BLASLT_ALGO_CAP_CUSTOM_MEMORY_ORDER)
#define CUBLASLT_ALGO_CAP_POINTER_MODE_MASK CUX(BLASLT_ALGO_CAP_POINTER_MODE_MASK)
#define CUBLASLT_ALGO_CAP_EPILOGUE_MASK CUX(BLASLT_ALGO_CAP_EPILOGUE_MASK)
#define CUBLASLT_ALGO_CAP_STAGES_IDS CUX(BLASLT_ALGO_CAP_STAGES_IDS)
#define CUBLASLT_ALGO_CAP_LD_NEGATIVE CUX(BLASLT_ALGO_CAP_LD_NEGATIVE)
#define CUBLASLT_ALGO_CAP_NUMERICAL_IMPL_FLAGS CUX(BLASLT_ALGO_CAP_NUMERICAL_IMPL_FLAGS)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_A_BYTES CUX(BLASLT_ALGO_CAP_MIN_ALIGNMENT_A_BYTES)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_B_BYTES CUX(BLASLT_ALGO_CAP_MIN_ALIGNMENT_B_BYTES)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_C_BYTES CUX(BLASLT_ALGO_CAP_MIN_ALIGNMENT_C_BYTES)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_D_BYTES CUX(BLASLT_ALGO_CAP_MIN_ALIGNMENT_D_BYTES)
#define CUBLASLT_ALGO_CAP_ATOMIC_SYNC CUX(BLASLT_ALGO_CAP_ATOMIC_SYNC)

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
 cuX(blasLtMatmulAlgoGetHeuristic(ltHandle, matmulDesc, layoutA, layoutB, \
           layoutC, layoutD, pref, n, heuristic_result, rslt))
#define cublasLtMatmulPreferenceDestroy(pref) cuX(blasLtMatmulPreferenceDestroy(pref))

#define cublasLtMatmulPreference_t cuX(blasLtMatmulPreference_t)
#define cublasLtMatmulPreferenceCreate(preference) cuX(blasLtMatmulPreferenceCreate(preference))

#define cublasLtMatmulPreferenceAttributes_t cuX(blasLtMatmulPreferenceAttributes_t)
#define cublasLtMatmulPreferenceSetAttribute(pref, arg1, ptr, size) \
	cuX(blasLtMatmulPreferenceSetAttribute(pref, arg1, ptr, size))

#define CUBLASLT_MATMUL_PREF_MAX_WORKSPACE_BYTES CUX(BLASLT_MATMUL_PREF_MAX_WORKSPACE_BYTES)

/**
 * D = alpha*(A*B) + beta*(C)
 */
#define cublasLtMatmul(lightHandle, computeDesc, alpha, A, Adesc, B, Bdesc, \
         beta, C, Cdesc, D, Ddesc, algo, workspace, \
         workspaceSizeInBytes, stream) \
 cuX(blasLtMatmul(lightHandle, computeDesc, alpha, A, Adesc, B, Bdesc, \
         beta, C, Cdesc, D, Ddesc, algo, workspace, \
         workspaceSizeInBytes, stream))

#ifdef __USE_HPCC__
# include <hcblas/hcblasLt.h>
#elif defined(__USE_LUCA__)
# ifdef LUCA_PHASE_II_PROJECT
#  include <lcblas/lcblasLt.h>
# else
#  include <hcblas/hcblasLt.h>
# endif
#elif defined(__USE_HIP__)
# ifdef __USE_HIP_V2__
#  define HIPBLAS_V2
# endif
# define HIPBLAS_USE_HIP_HALF
# include <hipblaslt/hipblaslt.h>
#endif

#endif
