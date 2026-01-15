#include <stdio.h>

#define __weak __attribute__((weak))

/**
 * This weak function maybe override by function in the other source code.
 */
int __weak func(void)
{
	return printf("weak function\n");
}

int main(void)
{
	func();
	return 0;
}
