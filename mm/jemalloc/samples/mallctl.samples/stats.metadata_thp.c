#include <stdio.h>
#include <jemalloc/jemalloc.h>

//stats.metadata_thp (size_t) r- [--enable-stats]
//	Number of transparent huge pages (THP) used for metadata. See stats.metadata and opt.metadata_thp) for details.

void get_jemalloc_stats_metadata_thp(size_t *value) {
	size_t size= sizeof(size_t);
	je_mallctl("stats.metadata_thp", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	size_t value = 1;

	get_jemalloc_stats_metadata_thp(&value);
	printf("value = %ld 0x%x\n", value, value);

	char *str = je_malloc(40440);
	str[40440-1] = 'A';

	je_mallctl("tcache.flush", NULL, NULL, NULL, 0);

	get_jemalloc_stats_metadata_thp(&value);
	printf("value = %ld\n", value);
}





