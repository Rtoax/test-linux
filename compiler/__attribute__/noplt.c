#include <stdio.h>

/**
 * The noplt attribute is the counterpart to option -fno-plt. Calls to
 * functions marked with this attribute in position-independent code do not
 * use the PLT.
 */
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
