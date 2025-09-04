// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#if defined(HAVE_HCCL)
# include <hc_runtime.h>
# include <hcblas/hcblas.h>
# include <hcblas/hcblasLt.h>
# include "hpcc_helpers.h"
# include "cuda_adapter.h"
#else
# include <cuda_runtime.h>
# include <cublas_v2.h>
# include <cublasLt.h>
# include "cuda_helpers.h"
#endif

#define m	2
#define n	3
#define k	4

void printMatrixLayout(const char* name, cublasLtMatrixLayout_t layout)
{
	uint32_t rows, cols;
	int32_t ld;
	cudaDataType type;

	cublasLtMatrixLayoutGetAttribute(layout, CUBLASLT_MATRIX_LAYOUT_ROWS, &rows, sizeof(rows), NULL);
	cublasLtMatrixLayoutGetAttribute(layout, CUBLASLT_MATRIX_LAYOUT_COLS, &cols, sizeof(cols), NULL);
	cublasLtMatrixLayoutGetAttribute(layout, CUBLASLT_MATRIX_LAYOUT_LD, &ld, sizeof(ld), NULL);
	cublasLtMatrixLayoutGetAttribute(layout, CUBLASLT_MATRIX_LAYOUT_TYPE, &type, sizeof(type), NULL);

	printf("%s Layout: rows=%u, cols=%u, ld=%d, type=%s\n",
		name, rows, cols, ld,
		(type == CUDA_R_32F) ? "FP32" :
		(type == CUDA_R_16F) ? "FP16" :
		(type == CUDA_R_8I) ? "INT8" : "Unknown");
}

int main(void)
{
	float alpha = 1.0f;
	float beta = 0.0f;

	float h_A[m * k] = {1, 2, 3, 4,
			5, 6, 7, 8};
	float h_B[k * n] = {1, 2, 3,
			4, 5, 6,
			7, 8, 9,
			10, 11, 12};
	float h_C[m * n] = {0};

	float *d_A, *d_B, *d_C;

	cublasLtHandle_t ltHandle;
	cublasLtMatmulDesc_t matmulDesc;
	cublasLtMatrixLayout_t layoutA, layoutB, layoutC;
	cublasLtMatmulPreference_t pref;
	cublasLtMatmulHeuristicResult_t heuristic_result;
	void *workspace;
	size_t workspaceSize = 1 << 22; // 4MB
	int rslt;


	CUDA_CHECK_EXIT(cudaMalloc((void**)&d_A, m * k * sizeof(float)));
	CUDA_CHECK_EXIT(cudaMalloc((void**)&d_B, k * n * sizeof(float)));
	CUDA_CHECK_EXIT(cudaMalloc((void**)&d_C, m * n * sizeof(float)));
	CUDA_CHECK_EXIT(cudaMemcpy(d_A, h_A, m * k * sizeof(float), cudaMemcpyHostToDevice));
	CUDA_CHECK_EXIT(cudaMemcpy(d_B, h_B, k * n * sizeof(float), cudaMemcpyHostToDevice));

	CUBLAS_CHECK(cublasLtCreate(&ltHandle), exit(EXIT_FAILURE));

	CUBLAS_CHECK(cublasLtMatmulDescCreate(&matmulDesc, CUBLAS_COMPUTE_32F, CUDA_R_32F), exit(EXIT_FAILURE));

	CUBLAS_CHECK(cublasLtMatrixLayoutCreate(&layoutA, CUDA_R_32F, m, k, m), exit(EXIT_FAILURE));
	CUBLAS_CHECK(cublasLtMatrixLayoutCreate(&layoutB, CUDA_R_32F, k, n, k), exit(EXIT_FAILURE));
	CUBLAS_CHECK(cublasLtMatrixLayoutCreate(&layoutC, CUDA_R_32F, m, n, m), exit(EXIT_FAILURE));

	printMatrixLayout("A", layoutA);
	printMatrixLayout("B", layoutB);
	printMatrixLayout("C", layoutC);

	CUDA_CHECK_EXIT(cudaMalloc(&workspace, workspaceSize));

	CUBLAS_CHECK(cublasLtMatmulPreferenceCreate(&pref), exit(EXIT_FAILURE));
	CUBLAS_CHECK(cublasLtMatmulPreferenceSetAttribute(pref,
			CUBLASLT_MATMUL_PREF_MAX_WORKSPACE_BYTES,
			&workspaceSize, sizeof(workspaceSize)), exit(EXIT_FAILURE));

	CUBLAS_CHECK(cublasLtMatmulAlgoGetHeuristic(ltHandle,
				matmulDesc, layoutA, layoutB, layoutC, layoutC,
				pref, 1, &heuristic_result, &rslt),);

	if (rslt == 0) {
		fprintf(stderr, "No valid algorithm found! Using fallback method.\n");
	} else {
		printf("Found %d heuristic algorithms\n", rslt);
	}

	CUBLAS_CHECK(cublasLtMatmul(
				ltHandle,
				matmulDesc,
				&alpha,
				d_A, layoutA,
				d_B, layoutB,
				&beta,
				d_C, layoutC,
				d_C, layoutC,
#if 1
				&heuristic_result.algo,
				workspace, workspaceSize,
#else
				NULL,
				NULL, 0,
#endif
				NULL /* No stream */), goto free);

	CUDA_CHECK_EXIT(cudaDeviceSynchronize());

	CUDA_CHECK_EXIT(cudaMemcpy(h_C, d_C, m * n * sizeof(float), cudaMemcpyDeviceToHost));

	printf("Result C = \n");
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j)
			printf("%f ", h_C[i * n + j]);
		printf("\n");
	}

free:
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
	cudaFree(workspace);
	cublasLtMatmulPreferenceDestroy(pref);
	cublasLtMatrixLayoutDestroy(layoutA);
	cublasLtMatrixLayoutDestroy(layoutB);
	cublasLtMatrixLayoutDestroy(layoutC);
	cublasLtMatmulDescDestroy(matmulDesc);
	cublasLtDestroy(ltHandle);

	return 0;
}
