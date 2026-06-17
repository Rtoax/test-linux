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
#include "__float128.h"

void test__float128(void)
{
#ifdef SUPPORT___float128
	assert(sizeof(__float128) == 16 &&
	       "size of __float128 is not equal to 16");

	__float128 pi = 3.1415926535897932384626433832795028Q;
	__float128 e = 2.7182818284590452353602874713526624Q;

	fp128_printf(pi, "%.35Qf");
	fp128_printf(pi, "%.35Qe");
	fp128_printf(pi, "%.35Qg");
	fp128_printf(e, "%.35Qf");
	fp128_printf(pi + e, "%.35Qf");

	fp128_printf(fmaq(pi, pi, pi), "%.35Qf");

	fp128_printf(sinq(pi), "%.35Qf");
	fp128_printf(cosq(pi), "%.35Qf");
	fp128_printf(tanq(pi), "%.35Qf");
#endif
}

void test_Float128(void)
{
#ifdef SUPPORT__Float128
	assert(sizeof(_Float128) == 16 &&
	       "size of _Float128 is not equal to 16");

	_Float128 pi = 3.1415926535897932384626433832795028Q;
	_Float128 e = 2.7182818284590452353602874713526624Q;

	fp128_printf(pi, "%.35Qf");
	fp128_printf(e, "%.35Qf");
	fp128_printf(pi + e, "%.35Qf");

	fp128_printf(fmaq(pi, pi, pi), "%.35Qf");

	fp128_printf(sinq(pi), "%.35Qf");
	fp128_printf(cosq(pi), "%.35Qf");
	fp128_printf(tanq(pi), "%.35Qf");
#endif
}

int main(void)
{
	test__float128();
	test_Float128();
	return 0;
}
