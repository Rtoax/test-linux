#include <immintrin.h>
#include <stdio.h>


#if 0
void daxpy2(int n, double a, const double x[], double y[])
{
	__m512d av = _mm512_set1_pd(a);
	int i, r = n & 7, n2 = n - r;

	for(i = -n2; i < 0; i += 8) {
		__m512d yv = _mm512_loadu_pd(&y[i + n2]);
		__m512d xv = _mm512_loadu_pd(&x[i + n2]);
		yv = _mm512_fmadd_pd(av, xv, yv);
		_mm512_storeu_pd(&y[i + n2], yv);
	}
	__m512d yv = _mm512_loadu_pd(&y[n2]);
	__m512d xv = _mm512_loadu_pd(&x[n2]);
	yv = _mm512_fmadd_pd(av, xv, yv);
	__mmask8 mask = (1 << r) - 1;
	//__mmask8 mask = _bextr_u32(-1, 0, r);
	_mm512_mask_storeu_pd(&y[n2], mask, yv);
}
#else
void daxpy2(size_t n, double a, const double x[], double y[])
{
	__m512d av = _mm512_set1_pd(a);
	size_t i, r = n&7, n2 = n & (-8);
	for(i = -n2; i != 0; i += 8) {
		__m512d yv = _mm512_loadu_pd(&y[i + n2]);
		__m512d xv = _mm512_loadu_pd(&x[i + n2]);
		yv = _mm512_fmadd_pd(av, xv, yv);
		_mm512_storeu_pd(&y[i + n2], yv);
	}
	//__mmask8 mask = _bzhi_u32(-1, r);
	__mmask8 mask = (1 << r) - 1;
	__m512d yv = _mm512_mask_loadu_pd(_mm512_undefined_pd (), mask, &y[n2]);
	__m512d xv = _mm512_mask_loadu_pd(_mm512_undefined_pd (), mask, &x[n2]);
	yv = _mm512_mask_fmadd_pd(av, mask, xv, yv);
	_mm512_mask_storeu_pd(&y[n2], mask, yv);
}
#endif

void add512(double a[], double b[], double c[])
{
	__m512d aa, bb, cc;
	aa = _mm512_loadu_pd(&a);
	bb = _mm512_loadu_pd(&b);
	cc = _mm512_add_pd(aa, bb);
	_mm512_storeu_pd(c, cc);
}

#define LEN	13

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
