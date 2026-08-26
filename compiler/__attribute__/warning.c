/**
 * warning ("message")
 *
 * This attribute applies to functions.
 */

#include <stdio.h>

#define __warning __attribute__((warning("Symbol is not public ABI")))

__warning void func1(void)
{
	printf("funcs\n");
}

int main(void)
{
	func1();
	return 0;
}
