#include <stdio.h>


/* The 'naked' attribute prevents the compiler from generating any
 * function entry or exit code */
#define _naked __attribute__((__naked__))

_naked int func1(void)
{
	return printf("rongtao\n");
}

int func2(void)
{
	return printf("rongtao\n");
}

int main(void)
{
	func1();
	func2();
	return 0;
}