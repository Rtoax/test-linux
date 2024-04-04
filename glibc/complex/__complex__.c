#include <stdio.h>
#include <complex.h>

int main(void)
{
	__complex__ c = 1 + 2 * _Complex_I;

	int i = __imag__ c;
	int r = __real__ c;

	printf("real %d, imag %d\n", i, r);
	return 0;
}
