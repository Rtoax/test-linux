#include <stdio.h>

#define __weak __attribute__((weak))

int __weak func(void)
{
	return printf("weak function\n");
}

/* maybe overwrite weak function in other c code */

int main(void)
{
	func();
	return 0;
}
