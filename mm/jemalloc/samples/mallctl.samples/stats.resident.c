#include <stdio.h>
#include <jemalloc/jemalloc.h>

//stats.resident (size_t) r- [--enable-stats]
//	Maximum number of bytes in physically resident data pages mapped by the allocator, comprising all pages dedicated to
//	allocator metadata, pages backing active allocations, and unused dirty pages. This is a maximum rather than precise
//	because pages may not actually be physically resident if they correspond to demand-zeroed virtual memory that has not
//	yet been touched. This is a multiple of the page size, and is larger than stats.active.

void get_jemalloc_stats_resident(size_t *value) {
	size_t size= sizeof(size_t);
	je_mallctl("stats.resident", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	size_t value = 1;

	get_jemalloc_stats_resident(&value);
	printf("value = %ld 0x%x\n", value, value);

	char *str = je_malloc(40440);
	str[40440-1] = 'A';

	je_mallctl("tcache.flush", NULL, NULL, NULL, 0);

	get_jemalloc_stats_resident(&value);
	printf("value = %ld\n", value);
}




