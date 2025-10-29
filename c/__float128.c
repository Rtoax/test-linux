/**
 * __float128 is available on i386, x86_64, IA-64, LoongArch and hppa HP-UX,
 * as well as on PowerPC GNU/Linux targets that enable the vector scalar (VSX)
 * instruction set. __float128 supports the 128-bit floating type. On i386,
 * x86_64, PowerPC, LoongArch and IA-64, other than HP-UX, __float128 is an
 * alias for _Float128. On hppa and IA-64 HP-UX, __float128 is an alias for
 * long double.
 */
#include <assert.h>
#include <stdio.h>
#include <stdint.h>

/**
 * GCC Additional Floating Types: https://gcc.gnu.org/onlinedocs/gcc/Floating-Types.html
 * - NVRTC on Linux
 * - GCC version 4.1 or later on x86_64/amd64
 * - Clang version 3.9 or later on x86_64/amd64
 * - NVHPC version 21.1 or later on x86_64/amd64
 */
#if (defined(__clang__) && (__clang_major__ >= 3 && __clang_minor__ >= 9)) || \
    (defined(__GNUC__) && (__GNUC__ >= 4))
# pragma message "Support __float128 arithmetic"
# define SUPPORT_FLOAT128_ARITHMETIC	1
#endif


void test__float128(void)
{
#ifdef SUPPORT___float128
	assert(sizeof(__float128) == 16 && "size of __float128 is not equal to 16");

	__float128 f128 = 3.14;
	printf("size of __float128 %ld\n", sizeof(f128));
#endif

}

void test_Float128(void)
{
#ifdef SUPPORT__Float128
	assert(sizeof(_Float128) == 16 && "size of _Float128 is not equal to 16");

	_Float128 F128 = 3.14;
	printf("size of _Float128 %ld\n", sizeof(F128));
#endif
}

int main(void)
{
	test__float128();
	test_Float128();
	return 0;
}
