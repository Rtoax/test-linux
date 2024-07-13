#include <stdio.h>
#include <jemalloc/jemalloc.h>

//stats.allocated (size_t) r- [--enable-stats]
//	Total number of bytes allocated by the application.

void get_jemalloc_stats_allocated(size_t *value) {
	size_t size= sizeof(size_t);
	je_mallctl("stats.allocated", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	size_t value = 1;

	get_jemalloc_stats_allocated(&value);
	printf("value = %ld 0x%x\n", value, value);

	char *str = je_malloc(40440);
	str[40440-1] = 'A';

	je_mallctl("tcache.flush", NULL, NULL, NULL, 0);

	get_jemalloc_stats_allocated(&value);
	printf("value = %ld\n", value);
}


