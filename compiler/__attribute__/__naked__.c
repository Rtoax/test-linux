#include <stdio.h>

/**
 * The 'naked' attribute prevents the compiler from generating any
 * function entry or exit code
 */
#define ____naked __attribute__((naked))
#define ____naked2 __attribute__((__naked__))

#if !defined(__clang__)
# define __naked	____naked
# define __naked2	____naked2
#else
/**
 * FIXME: clang error: non-ASM statement in naked function is not supported
 */
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

__naked2 void func4(void)
{
	__asm__("nop\n");
}

int main(void)
{
	func1();
	func2();
	func3();
	return 0;
}
