#include <stdio.h>

/*
 * Note the missing underscores.
 *
 *   gcc: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-noinline-function-attribute
 * clang: mentioned
 */
#define noinline __attribute__((noinline))
#define noinline2 __attribute__((__noinline__))

static noinline void foo(void)
{
	printf("hello\n");
}

static noinline2 void bar(void)
{
	printf("hello\n");
}

int main(void)
{
	foo();
	bar();
	return 0;
}
