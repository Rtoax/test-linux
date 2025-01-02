#include <stdio.h>

/**
 * The 'naked' attribute prevents the compiler from generating any
 * function entry or exit code
 */
#if !defined(__clang__)
# define __naked __attribute__((naked))
# define __naked2 __attribute__((__naked__))
#else
// FIXME: clang??
# define __naked
# define __naked2
#endif

__naked int func1(void)
{
	return printf("rongtao naked\n");
}

__naked2 int func2(void)
{
	return printf("rongtao naked2\n");
}

int func3(void)
{
	return printf("rongtao\n");
}

int main(void)
{
	func1();
	func2();
	func3();
	return 0;
}
