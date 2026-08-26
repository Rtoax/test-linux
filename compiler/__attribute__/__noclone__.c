/**
 * This attribute applies to functions.
 *
 * This attribute prevents a function from being considered for cloning, a
 * mechanism that produces specialized copies of functions and which is
 * (currently) performed by interprocedural constant propagation.
 *
 * Refs:
 * - gcc: https://gcc.gnu.org/onlinedocs/gcc/Common-Attributes.html#index-noclone
 * - clang: not support yet.
 */
#include <stdio.h>

#if __has_attribute(__noclone__)
#define __noclone __attribute__((__noclone__))
#else
#define __noclone
#endif

__noclone void foo_noclone(void)
{
}

void foo(void)
{
}

int main(void)
{
	foo_noclone();
	foo();

	return 0;
}
