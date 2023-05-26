#include <stdint.h>

#include <wmmintrin.h>
#include <x86intrin.h>
#include <immintrin.h>


static __m128i aesdec(void)
{
    __m128i a = _mm_set_epi8(0x03, 0x06, 0x09, 0x0c, 0x0f, 0x02, 0x05, 0x08,
                                0x0b, 0x0e, 0x01, 0x04, 0x07, 0x0a, 0x0d, 0x00);
	__m128i b = _mm_setzero_si128();

	return _mm_aesdec_si128(a, b);
}

int main(void)
{
	__m128i x = aesdec();
}
