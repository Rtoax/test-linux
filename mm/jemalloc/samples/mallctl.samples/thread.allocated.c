#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//thread.allocated (uint64_t) r- [--enable-stats]
//	Get the total number of bytes ever allocated by the calling thread. This counter has the potential to wrap around; it
//	is up to the application to appropriately interpret the counter in such cases.

void get_jemalloc_thread_allocated(uint64_t *value)
{
	size_t size = sizeof(uint64_t);
	je_mallctl("thread.allocated", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	uint64_t value = 1;

	get_jemalloc_thread_allocated(&value);
	printf("value = %ld\n", value);

	char *str = je_malloc(1025);

	get_jemalloc_thread_allocated(&value);
	printf("value = %ld\n", value);
}


