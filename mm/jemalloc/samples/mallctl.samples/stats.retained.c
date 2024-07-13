#include <stdio.h>
#include <jemalloc/jemalloc.h>

//stats.retained (size_t) r- [--enable-stats]
//	Total number of bytes in virtual memory mappings that were retained rather than being returned to the operating
//	system via e.g. munmap(2) or similar. Retained virtual memory is typically untouched, decommitted, or purged, so it
//	has no strongly associated physical memory (see extent hooks for details). Retained memory is excluded from mapped
//	memory statistics, e.g. stats.mapped.

void get_jemalloc_stats_retained(size_t *value) {
	size_t size= sizeof(size_t);
	je_mallctl("stats.retained", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	size_t value = 1;

	get_jemalloc_stats_retained(&value);
	printf("value = %ld 0x%x\n", value, value);

	char *str = je_malloc(40440);
	str[40440-1] = 'A';

	je_mallctl("tcache.flush", NULL, NULL, NULL, 0);

	get_jemalloc_stats_retained(&value);
	printf("value = %ld\n", value);
}




