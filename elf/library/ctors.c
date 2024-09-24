#include <stdio.h>

#define debug() do { \
		printf("[%s:%s %d]\n", __FILE__, __func__, __LINE__); \
	} while(0)

static void __attribute__((constructor(101))) before1(void)
{
	debug();
}

static void __attribute__((constructor(109))) before2(void)
{
	debug();
}

static void __attribute__((destructor(101))) after1(void)
{
	debug();
}

static void __attribute__((destructor(109))) after2(void)
{
	debug();
}

int foo_ctor(void)
{
	printf("call foo_ctor.\n");
}
