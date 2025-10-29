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
#ifdef __has_include
# if __has_include (<quadmath.h>)
#  include <quadmath.h>
#  pragma message "compiler support quadmath.h"
#  define HAVE_quadmath_h	1
# endif
#endif

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

#ifdef HAVE_quadmath_h
#define fp128_printf(fp128, tfmt) do {	\
		char __buf[128];	\
		quadmath_snprintf(__buf, sizeof(__buf), tfmt, fp128);	\
		printf(#fp128 " = %s\n", __buf);	\
	} while (0)
#else
#define fp128_printf(fp128, tfmt) do {	\
		(void)fp128;	\
	} while (0)
#endif

void test__float128(void)
{
#ifdef SUPPORT___float128
	assert(sizeof(__float128) == 16 && "size of __float128 is not equal to 16");

	__float128 pi = 3.1415926535897932384626433832795028Q;
	__float128 e = 2.7182818284590452353602874713526624Q;

	fp128_printf(pi, "%.35Qf");
	fp128_printf(pi, "%.35Qe");
	fp128_printf(pi, "%.35Qg");
	fp128_printf(e, "%.35Qf");
	fp128_printf(pi + e, "%.35Qf");
#endif

}

void test_Float128(void)
{
#ifdef SUPPORT__Float128
	assert(sizeof(_Float128) == 16 && "size of _Float128 is not equal to 16");

	_Float128 pi = 3.1415926535897932384626433832795028Q;
	_Float128 e = 2.7182818284590452353602874713526624Q;

	fp128_printf(pi, "%.35Qf");
	fp128_printf(e, "%.35Qf");
	fp128_printf(pi + e, "%.35Qf");
#endif
}

int main(void)
{
	test__float128();
	test_Float128();
	return 0;
}
