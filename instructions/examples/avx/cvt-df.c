#include <stdio.h>
#include <x86intrin.h>

#define N 128

int main(void)
{
	float a[N]={0};
	double b[N]={1,2,3};
	int i;

	/**
	 * for (i = 0; i < N; i++)
	 *	a[i] = b[i];
	 */

	int block = N / 4;
	__m256d ymm_pd;
	__m128 ymm_ps;

	for(i = 0; i < block; i++){
		ymm_pd = _mm256_loadu_pd(b + i*4);
		ymm_ps = _mm256_cvtpd_ps(ymm_pd);
		//printf("%f, %f, %f, %f\n",
		//		ymm_ps[0], ymm_ps[1], ymm_ps[2], ymm_ps[3]);
		_mm_storeu_ps(a + i*4,ymm_ps);
	}
	if (a[2] == 3)
		printf("Success\n");
	else
		printf("Failed\n");
	return 0;
}

