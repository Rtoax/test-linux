/**
 * __float80 is available on the i386, x86_64, and IA-64 targets, and supports
 * the 80-bit (XFmode) floating type. It is an alias for the type name _Float64x
 * on these targets.
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>


int main(void)
{
	assert(sizeof(__float80) == 16 && "size of __float80 is not equal to 16");

	__float80 f80 = 3.14;
	_Float64x f64x = 3.14;

	printf("size of __float80 %ld\n", sizeof(f80));
	printf("size of _Float64x %ld\n", sizeof(f64x));

	return 0;
}
