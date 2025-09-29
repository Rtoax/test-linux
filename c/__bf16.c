#include <stdio.h>
#include <stdint.h>

/**
 * gcc git://gcc.gnu.org/git/gcc.git
 * - commit 0a329ecf1137 ("libgcc, Darwin: Update symbol exports to include bitint and bf.")
 * - commit 13071c3c7d1b ("aarch64: Add bfloat16_t support for aarch64")
 * - commit c2565a31c162 ("middle-end, c++, i386, libgcc: std::bfloat16_t and __bf16 arithmetic support")
 */
#if defined(__GNUC__) && (__GNUC__ >= 13)
/* FIXME: support clang, not only __GNUC__ */
# define SUPPORT_BF16_ARITHMETIC	1
#endif

__bf16 __floattobf16(float fp32)
{
#ifdef SUPPORT_BF16_ARITHMETIC
	return fp32;
#else
	uint32_t float_bits = *(uint32_t *)&fp32;
	uint16_t bf16_bits = (uint16_t)(float_bits >> 16);
	__bf16 *bf16 = (__bf16 *)&bf16_bits;
	return *bf16;
#endif
}

float __bf16tofloat(__bf16 bf16)
{
#ifdef SUPPORT_BF16_ARITHMETIC
	return bf16;
#else
	uint16_t bf16_bits = *(uint16_t *)&bf16;
	uint32_t float_bits = (uint32_t)(bf16_bits << 16);
	float fp32 = *(float *)&float_bits;
	return fp32;
#endif
}

__bf16 __bf16mul(__bf16 a, __bf16 b)
{
#ifdef SUPPORT_BF16_ARITHMETIC
	return a * b;
#else
	float fa = __bf16tofloat(a);
	float fb = __bf16tofloat(b);
	return __floattobf16(fa + fb);
#endif
}

int main(void)
{
	__bf16 a = __floattobf16(-3.141592653f);
	__bf16 b = a;
	__bf16 c = __bf16mul(a, b);

	printf("%f\n", __bf16tofloat(c));

	return 0;
}
