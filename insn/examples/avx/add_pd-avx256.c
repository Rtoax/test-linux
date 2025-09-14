#include <immintrin.h>
#include <stdio.h>


void daxpy2(size_t n, double a, const double x[], double y[])
{
	size_t i, n2 = n & (-4);
	for(i = -n2; i != 0; i += 4) {
		__m256d yv = _mm256_loadu_pd(&y[i + n2]);
		__m256d xv = _mm256_loadu_pd(&x[i + n2]);
		yv = _mm256_add_pd(xv, yv);
		_mm256_storeu_pd(&y[i + n2], yv);
	}
}

#define LEN	64

int main(void)
{
	int i;
	double a[LEN];
	double b[LEN];

	for (i = 0; i < LEN; i++) {
		a[i] = i + 1;
		b[i] = i + 1;
	}

	daxpy2(LEN, 2, a, b);

	for (i = 0; i < LEN; i++)
		printf("%f ", b[i]);
	printf("\n");

	return 0;
}
