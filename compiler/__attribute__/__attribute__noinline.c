#include <stdio.h>

/*
 * Note the missing underscores.
 *
 *   gcc: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-noinline-function-attribute
 * clang: mentioned
 */
#define noinline __attribute__((__noinline__))

static noinline void foo(void)
{
	printf("hello\n");
}

int main(void)
{
	foo();
	return 0;
}
