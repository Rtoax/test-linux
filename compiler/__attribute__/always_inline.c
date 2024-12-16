#include <stdio.h>

static inline void __attribute__((always_inline)) foo(void)
{
	printf("hello\n");
}

int main(void)
{
	foo();
	return 0;
}
