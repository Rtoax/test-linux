#include <stdlib.h>
#include <string.h>
#include <immintrin.h>

__m512i avx512_test(__m512i x0, __m512i x1, __m512i x2, __m512i x3,
		    __m512i x4, __m512i x5, __m512i x6, __m512i x7)
{
	__m512i zmm;

	zmm = _mm512_set1_epi32(0);
	if (memcmp(&zmm, &x0, sizeof(zmm)))
		abort();

	zmm = _mm512_set1_epi32(1);
	if (memcmp(&zmm, &x1, sizeof(zmm)))
		abort();

	zmm = _mm512_set1_epi32(2);
	if (memcmp(&zmm, &x2, sizeof(zmm)))
		abort();

	zmm = _mm512_set1_epi32(3);
	if (memcmp(&zmm, &x3, sizeof(zmm)))
		abort();

	zmm = _mm512_set1_epi32(4);
	if (memcmp(&zmm, &x4, sizeof(zmm)))
		abort();

	zmm = _mm512_set1_epi32(5);
	if (memcmp(&zmm, &x5, sizeof(zmm)))
		abort();

	zmm = _mm512_set1_epi32(6);
	if (memcmp(&zmm, &x6, sizeof(zmm)))
		abort();

	zmm = _mm512_set1_epi32(7);
	if (memcmp(&zmm, &x7, sizeof(zmm)))
		abort();

	return _mm512_set1_epi32(0x12349876);
}

int tst_avx512_aux(void)
{
	__m512i zmm0 = _mm512_set1_epi32(0);
	__m512i zmm1 = _mm512_set1_epi32(1);
	__m512i zmm2 = _mm512_set1_epi32(2);
	__m512i zmm3 = _mm512_set1_epi32(3);
	__m512i zmm4 = _mm512_set1_epi32(4);
	__m512i zmm5 = _mm512_set1_epi32(5);
	__m512i zmm6 = _mm512_set1_epi32(6);
	__m512i zmm7 = _mm512_set1_epi32(7);

	__m512i ret = avx512_test(zmm0, zmm1, zmm2, zmm3, zmm4, zmm5, zmm6, zmm7);
	zmm0 = _mm512_set1_epi32(0x12349876);

	if (memcmp(&zmm0, &ret, sizeof(ret)))
		abort();
	return 0;
}

int main(void)
{
	tst_avx512_aux();
	return 0;
}
