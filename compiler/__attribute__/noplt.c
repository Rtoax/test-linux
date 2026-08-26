/**
 * The noplt attribute is the counterpart to option -fno-plt. Calls to
 * functions marked with this attribute in position-independent code do not
 * use the PLT.
 *
 * Refs:
 * - gcc: https://gcc.gnu.org/onlinedocs/gcc/Common-Attributes.html#index-noplt
 */
#include <stdio.h>

#ifndef __clang__
# define __noplt	__attribute__((noplt))
#else
# define __noplt
#endif

#ifdef NOPLT
int getchar(void) __noplt;
#endif

int main(void)
{
	getchar();
	return 0;
}
