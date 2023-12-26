#include <immintrin.h>
#include <stdio.h>


void add512(double a[], double b[], double c[])
{
	_mm512_storeu_pd(&c, _mm512_add_pd(_mm512_loadu_pd(&a), _mm512_loadu_pd(&b)));
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
