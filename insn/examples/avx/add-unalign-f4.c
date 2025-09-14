#include <stdio.h>
#include <x86intrin.h>

#define N 128

int main(void)
{
	double a[N], b[N], c[N];

	int i;

	for (i = 0; i < N; i++)
		a[i] = 3;
	for (i = 0; i < N; i++)
		b[i] = 4;

	/**
	 * for (i = 0; i < N / 4(32); i++)
	 *	c[i] = a[i + 1] + b[i + 2];
	 */
	int block = N / 4 / 4;
	__m256d avx_sum0 = _mm256_setzero_pd();
	__m256d ymm0, ymm1;

	for (i = 0; i < block; i++){
		ymm0 = _mm256_loadu_pd(a + 1 + i * 4);
		ymm1 = _mm256_loadu_pd(b + 1 + i * 4);

		avx_sum0 = _mm256_add_pd(avx_sum0, ymm0);
		avx_sum0 = _mm256_add_pd(avx_sum0, ymm1);
		_mm256_storeu_pd(c + i*4, avx_sum0);
		avx_sum0 = _mm256_setzero_pd();
	}

	if (c[2] == 7)
		printf("Success\n");
	else
		printf("Failed\n");
	return 0;
}

