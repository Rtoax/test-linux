#include <stdio.h>
#include <stdalign.h>
#include <immintrin.h>

int main(void)
{
	int i, len = 3200;

	/* Dynamic memory allocation with 32-byte alignment */
	float* pInVector = (float *)_mm_malloc(len * sizeof(float), 32);
	float* pOutVector = (float *)_mm_malloc(len * sizeof(float), 32);

	/* init data */
	for (i = 0; i < len; i++)
		pInVector[i] = 1;

	float cos_teta = 0.8660254037;
	float sin_teta = 0.5;

	/* Static memory allocation of 8 floats with 32-byte alignments */
	alignas(32) float cos_sin_teta_vec[8] = {cos_teta, sin_teta, cos_teta, sin_teta,
						cos_teta, sin_teta, cos_teta, sin_teta};
	alignas(32) float sin_cos_teta_vec[8] = {sin_teta, cos_teta, sin_teta, cos_teta,
						sin_teta, cos_teta, sin_teta, cos_teta};

	/* __m256 data type represents a Ymm register with 8 float elements */
	__m256 Ymm_cos_sin = _mm256_load_ps(cos_sin_teta_vec);

	/* Intel® AVX2 256-bit packed single load */
	__m256 Ymm_sin_cos = _mm256_load_ps(sin_cos_teta_vec);
	__m256 Ymm0, Ymm1, Ymm2, Ymm3;

	/* processing 16 elements in an unrolled twice loop */
	for (i = 0; i < len; i += 16) {
		Ymm0 = _mm256_load_ps(pInVector + i);
		Ymm1 = _mm256_moveldup_ps(Ymm0);
		Ymm2 = _mm256_movehdup_ps(Ymm0);
		Ymm2 = _mm256_mul_ps(Ymm2, Ymm_sin_cos);
		Ymm3 = _mm256_fmaddsub_ps(Ymm1, Ymm_cos_sin, Ymm2);
		_mm256_store_ps(pOutVector + i, Ymm3);

		Ymm0 = _mm256_load_ps(pInVector + i + 8);
		Ymm1 = _mm256_moveldup_ps(Ymm0);
		Ymm2 = _mm256_movehdup_ps(Ymm0);
		Ymm2 = _mm256_mul_ps(Ymm2, Ymm_sin_cos);
		Ymm3 = _mm256_fmaddsub_ps(Ymm1, Ymm_cos_sin, Ymm2);
		_mm256_store_ps(pOutVector + i + 8, Ymm3);
	}

	for (i = 0; i < len; i++)
		printf("%f - %f\n", pInVector[i], pOutVector[i]);

	_mm_free(pInVector);
	_mm_free(pOutVector);
	return 0;
}
