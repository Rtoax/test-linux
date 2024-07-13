#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//thread.arena (unsigned) rw
//	Get or set the arena associated with the calling thread. If the specified arena was not initialized beforehand (see
//	the arena.i.initialized mallctl), it will be automatically initialized as a side effect of calling this interface.

void set_jemalloc_thread_arena(unsigned value)
{
	je_mallctl("thread.arena", NULL, 0, &value, sizeof(value));
}
void get_jemalloc_thread_arena(unsigned *value)
{
	size_t size = sizeof(unsigned);
	je_mallctl("thread.arena", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	unsigned value = 1;

	get_jemalloc_thread_arena(&value);
	printf("value = %d\n", value);

	value = 1;

	set_jemalloc_thread_arena(value);

	get_jemalloc_thread_arena(&value);
	printf("value = %d\n", value);
}

