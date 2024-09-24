#include <stdio.h>

#define debug() do { \
		printf("[%s:%s %d]\n", __FILE__, __func__, __LINE__); \
	} while(0)

void __attribute__((constructor(101))) before1(void)
{
	debug();
}

void __attribute__((destructor(101))) after1(void)
{
	debug();
}

int foo(void)
{
	printf("call foo.\n");
	return 314;
}
