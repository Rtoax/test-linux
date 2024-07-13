#include <stdio.h>
#include <jemalloc/jemalloc.h>

//stats.metadata (size_t) r- [--enable-stats]
//	Total number of bytes dedicated to metadata, which comprise base allocations used for bootstrap-sensitive allocator
//	metadata structures (see stats.arenas.<i>.base) and internal allocations (see stats.arenas.<i>.internal). Transparent
//	huge page (enabled with opt.metadata_thp) usage is not considered.

void get_jemalloc_stats_metadata(size_t *value) {
	size_t size= sizeof(size_t);
	je_mallctl("stats.metadata", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	size_t value = 1;

	get_jemalloc_stats_metadata(&value);
	printf("value = %ld 0x%x\n", value, value);

	char *str = je_malloc(40440);
	str[40440-1] = 'A';

	je_mallctl("tcache.flush", NULL, NULL, NULL, 0);

	get_jemalloc_stats_metadata(&value);
	printf("value = %ld\n", value);
}




