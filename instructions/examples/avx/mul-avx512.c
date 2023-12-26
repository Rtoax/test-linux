#include <stdio.h>
#include <stdalign.h>
#include <immintrin.h>


int main(void)
{
	int i, len = 3200;

	/* Dynamic memory allocation with 64-byte alignment */
	float* pInVector = (float *)_mm_malloc(len * sizeof(float), 64);
	float* pOutVector = (float *)_mm_malloc(len * sizeof(float), 64);

	/* init data */
	for (i = 0; i < len; i++)
		pInVector[i] = 1;

	float cos_teta = 0.8660254037;
	float sin_teta = 0.5;

	/* Static memory allocation of 16 floats with 64-byte alignments */
	alignas(64) float cos_sin_teta_vec[16] = {cos_teta, sin_teta, cos_teta, sin_teta, cos_teta, sin_teta,
						cos_teta, sin_teta, cos_teta, sin_teta, cos_teta, sin_teta,
						cos_teta, sin_teta, cos_teta, sin_teta};
	alignas(64) float sin_cos_teta_vec[16] = {sin_teta, cos_teta, sin_teta, cos_teta, sin_teta, cos_teta,
						sin_teta, cos_teta, sin_teta, cos_teta, sin_teta, cos_teta,
						sin_teta, cos_teta, sin_teta, cos_teta};

	/* __m512 data type represents a Zmm register with 16 float elements */
	__m512 Zmm_cos_sin = _mm512_load_ps(cos_sin_teta_vec);

	/* Intel® AVX-512 512-bit packed single load */
	__m512 Zmm_sin_cos = _mm512_load_ps(sin_cos_teta_vec);
	__m512 Zmm0, Zmm1, Zmm2, Zmm3;

	/* processing 32 elements in an unrolled twice loop */
	for(i = 0; i < len; i += 32) {
		Zmm0 = _mm512_load_ps(pInVector + i);
		Zmm1 = _mm512_moveldup_ps(Zmm0);
		Zmm2 = _mm512_movehdup_ps(Zmm0);
		Zmm2 = _mm512_mul_ps(Zmm2, Zmm_sin_cos);
		Zmm3 = _mm512_fmaddsub_ps(Zmm1, Zmm_cos_sin, Zmm2);
		_mm512_store_ps(pOutVector + i, Zmm3);

		Zmm0 = _mm512_load_ps(pInVector + i + 16);
		Zmm1 = _mm512_moveldup_ps(Zmm0);
		Zmm2 = _mm512_movehdup_ps(Zmm0);
		Zmm2 = _mm512_mul_ps(Zmm2, Zmm_sin_cos);
		Zmm3 = _mm512_fmaddsub_ps(Zmm1, Zmm_cos_sin, Zmm2);
		_mm512_store_ps(pOutVector + i + 16, Zmm3);
	}

	for (i = 0; i < len; i++)
		printf("%f - %f\n", pInVector[i], pOutVector[i]);

	_mm_free(pInVector);
	_mm_free(pOutVector);
	return 0;
}
