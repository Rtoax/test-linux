#include <immintrin.h>
#include <stdio.h>


void add512(double a[], double b[], double c[])
{
	__m512d aa, bb, cc;
	aa = _mm512_loadu_pd(&a);
	bb = _mm512_loadu_pd(&b);
	cc = _mm512_add_pd(aa, bb);
	_mm512_storeu_pd(c, cc);
}

int main(void)
{
	int i;
	double a[8];
	double b[8];
	double c[8];

	for (i = 0; i < 8; i++) {
		a[i] = i + 1;
		b[i] = i + 1;
	}

	add512(a, b, c);

	for (i = 0; i < 8; i++)
		printf("%f ", c[i]);
	printf("\n");

	return 0;
}
