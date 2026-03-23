#include <stdio.h>

/* avoid sys/cdefs.h definition of '__always_inline' */
#undef __always_inline
#define __always_inline inline __attribute__((always_inline))

static void __always_inline foo(void)
{
	printf("hello\n");
}

int main(void)
{
	foo();
	return 0;
}
