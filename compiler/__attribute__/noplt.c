#include <stdio.h>

#ifdef NOPLT
/**
 * The noplt attribute is the counterpart to option -fno-plt. Calls to
 * functions marked with this attribute in position-independent code do not
 * use the PLT.
 */
int getchar(void) __attribute__((noplt));
#endif

int main(void)
{
	getchar();
	return 0;
}
