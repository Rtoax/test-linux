#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//thread.deallocated (uint64_t) r- [--enable-stats]
//	Get the total number of bytes ever deallocated by the calling thread. This counter has the potential to wrap around;
//	it is up to the application to appropriately interpret the counter in such cases.

void get_jemalloc_thread_deallocated(uint64_t *value)
{
	size_t size = sizeof(uint64_t);
	je_mallctl("thread.deallocated", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	uint64_t value = 1;

	get_jemalloc_thread_deallocated(&value);
	printf("value = %ld\n", value);

	char *str = je_malloc(1025);

	get_jemalloc_thread_deallocated(&value);
	printf("value = %ld\n", value);

	je_free(str);

	get_jemalloc_thread_deallocated(&value);
	printf("value = %ld\n", value);
}



