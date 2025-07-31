#include <stdio.h>
#if defined(HAVE_HCCL)
# include <hc_runtime.h>
# include <hcblas/hcblas.h>
# include <hcblas/hcblasLt.h>
# include "hpcc_helpers.h"
# include "cuda2hccl.h"
#else
# include <cuda_runtime.h>
# include <cublas_v2.h>
# include <cublasLt.h>
# include "cuda_helpers.h"
#endif

#define m	2
#define n	3
#define k	4

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
	CUDA_BUG_CALL_EXIT(cudaMalloc((void**)&d_A, m * k * sizeof(float)));
	CUDA_BUG_CALL_EXIT(cudaMalloc((void**)&d_B, k * n * sizeof(float)));
	CUDA_BUG_CALL_EXIT(cudaMalloc((void**)&d_C, m * n * sizeof(float)));
	CUDA_BUG_CALL_EXIT(cudaMemcpy(d_A, h_A, m * k * sizeof(float), cudaMemcpyHostToDevice));
	CUDA_BUG_CALL_EXIT(cudaMemcpy(d_B, h_B, k * n * sizeof(float), cudaMemcpyHostToDevice));

	cublasLtHandle_t ltHandle;
	CUDA_BLAS_BUG_CALL(cublasLtCreate(&ltHandle), exit(EXIT_FAILURE));

	cublasLtMatmulDesc_t matmulDesc;
	CUDA_BLAS_BUG_CALL(cublasLtMatmulDescCreate(&matmulDesc, CUBLAS_COMPUTE_32F, CUDA_R_32F), exit(EXIT_FAILURE));

	cublasLtMatrixLayout_t layoutA, layoutB, layoutC;
	CUDA_BLAS_BUG_CALL(cublasLtMatrixLayoutCreate(&layoutA, CUDA_R_32F, m, k, k), exit(EXIT_FAILURE));
	CUDA_BLAS_BUG_CALL(cublasLtMatrixLayoutCreate(&layoutB, CUDA_R_32F, k, n, n), exit(EXIT_FAILURE));
	CUDA_BLAS_BUG_CALL(cublasLtMatrixLayoutCreate(&layoutC, CUDA_R_32F, m, n, n), exit(EXIT_FAILURE));

	void* workspace;
	size_t workspaceSize = 1 << 22; // 4MB
	CUDA_BUG_CALL_EXIT(cudaMalloc(&workspace, workspaceSize));

	CUDA_BLAS_BUG_CALL(cublasLtMatmul(
				ltHandle,
				matmulDesc,
				&alpha,
				d_A, layoutA,
				d_B, layoutB,
				&beta,
				d_C, layoutC,
				d_C, layoutC,
				NULL,
				workspace, workspaceSize,
				0 /* No stream */), goto free);

	CUDA_BUG_CALL_EXIT(cudaMemcpy(h_C, d_C, m * n * sizeof(float), cudaMemcpyDeviceToHost));

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
	cublasLtMatrixLayoutDestroy(layoutA);
	cublasLtMatrixLayoutDestroy(layoutB);
	cublasLtMatrixLayoutDestroy(layoutC);
	cublasLtMatmulDescDestroy(matmulDesc);
	cublasLtDestroy(ltHandle);

	return 0;
}
