#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define debug() do { \
		printf("[%s:%s %d]\n", __FILE__, __func__, __LINE__); \
	} while(0)

void __attribute__((constructor)) before_in_obj(void)
{
	debug();
}
void __attribute__((constructor(101))) before1_in_obj(void)
{
	debug();
}
void __attribute__((constructor(102))) before2_in_obj(void)
{
	debug();
}

void __attribute__((destructor)) after_in_obj(void)
{
	debug();
}
void __attribute__((destructor(101))) after1_in_obj(void)
{
	debug();
}
void __attribute__((destructor(102))) after2_in_obj(void)
{
	debug();
}
