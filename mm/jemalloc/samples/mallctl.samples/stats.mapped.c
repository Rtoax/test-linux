#include <stdio.h>
#include <jemalloc/jemalloc.h>

//stats.mapped (size_t) r- [--enable-stats]
//	Total number of bytes in active extents mapped by the allocator. This is larger than stats.active. This does not
//	include inactive extents, even those that contain unused dirty pages, which means that there is no strict ordering
//	between this and stats.resident.

void get_jemalloc_stats_mapped(size_t *value) {
	size_t size= sizeof(size_t);
	je_mallctl("stats.mapped", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	size_t value = 1;

	get_jemalloc_stats_mapped(&value);
	printf("value = %ld 0x%x\n", value, value);

	char *str = je_malloc(40440);
	str[40440-1] = 'A';

	je_mallctl("tcache.flush", NULL, NULL, NULL, 0);

	get_jemalloc_stats_mapped(&value);
	printf("value = %ld\n", value);
}





