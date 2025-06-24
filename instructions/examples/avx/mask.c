#include <stdio.h>
#include <stdalign.h>
#include <immintrin.h>

int N;
double* restrict a;
double* restrict b;
double* restrict c;

void mask_c(void)
{
	int i;
	for (i = 0; i < N; i++)	{
		double res = b[i];
		if (a[i] > 1.0)
			res = res * a[i];
		c[i] = res;
	}
}

void mask_avx256(void)
{
	int i, j;
	for (i = 0; i < N; i += 32) {
		__m256d aa, bb, mask;
		#pragma GCC unroll(8)
		for (j = 0; j < 8; j++) {
			aa = _mm256_loadu_pd(a + i + j * 4);
			bb = _mm256_loadu_pd(b + i + j * 4);
			mask = _mm256_cmp_pd(_mm256_set1_pd(1.0), aa, 1);
			aa = _mm256_and_pd(aa, mask); // zero the false values
			aa = _mm256_mul_pd(aa, bb);
			bb = _mm256_blendv_pd(bb, aa, mask);
			_mm256_storeu_pd(c + 4 * j, bb);
		}
		c += 32;
	}
}

void mask_avx512(void)
{
	int i, j;
	for (i = 0; i < N; i += 32) {
		__m512d aa, bb;
		__mmask8 mask;
		#pragma GCC unroll(4)
		for (j = 0; j < 4; j++) {
			aa = _mm512_loadu_pd(a + i + j * 8);
			bb = _mm512_loadu_pd(b + i + j * 8);
			mask = _mm512_cmp_pd_mask(_mm512_set1_pd(1.0), aa, 1);
			bb = _mm512_mask_mul_pd(bb, mask, aa, bb);
			_mm512_storeu_pd(c + 8 * j, bb);
		}
		c += 32;
	}
}

void alloc_data(int n)
{
	int i;
	N = n;
	a = malloc(sizeof(double) * N);
	b = malloc(sizeof(double) * N);
	c = malloc(sizeof(double) * N);

	for (i = 0; i < N; i++) {
		if (i % 2)
			a[i] = 2;
		else
			a[i] = 1;
		b[i] = 2;
	}
}

void print_data(int n)
{
	int i;
	for (i = 0; i < n; i++) {
		printf("%2.1lf %2.1lf %2.1lf\n", a[i], b[i], c[i]);
	}
}

void free_data(void)
{
	free(a);
	free(b);
	free(c);
	a = b = c = NULL;
	N = 0;
}

int main(void)
{
	alloc_data(1024);
	mask_c();
	print_data(N);
	free_data();

	/* TODO: Compare avx */

	return 0;
}
