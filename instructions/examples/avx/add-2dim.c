#include <stdio.h>
#include <x86intrin.h>

#define N 128

int add_c(double a[N][N], double b[N][N], double c[N][N])
{
	int i, j;
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++)
			c[i][j] = a[i][j] + b[i][j];
	}
	return 0;
}

int add_avx2(double a[N][N], double b[N][N], double c[N][N])
{
	int i, j;
	int block = N / 4;
	__m256d ymm0, ymm1;
	__m256d avx_sum0 = _mm256_setzero_pd();
	for (i = 0; i < N; i++){
		for (j = 0; j < block; j ++) {
			ymm0 = _mm256_loadu_pd(&a[i][j * 4]);
			ymm1 = _mm256_loadu_pd(&b[i][j * 4]);
			avx_sum0 = _mm256_add_pd(ymm0, ymm1);
			_mm256_storeu_pd(*(c + i) + j * 4, avx_sum0);
		}
	}
	return 0;
}

int main(void)
{
	int i, j;
	double a[N][N], b[N][N], c[N][N];

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			 a[i][j] = 10;
			 b[i][j] = 6;
			 c[i][j] = 0;
		}
	}

	add_avx2(a, b, c);

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			if (c[i][j] != 16) {
				printf("Failed on [%d][%d]\n", i, j);
				exit(1);
			}
	printf("Success\n");
	return 0;
}

