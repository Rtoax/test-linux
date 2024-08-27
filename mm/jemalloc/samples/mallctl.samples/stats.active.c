#include <stdio.h>
#include <jemalloc/jemalloc.h>

//stats.active (size_t) r- [--enable-stats]
//	Total number of bytes in active pages allocated by the application. This is a multiple of the page size, and greater
//	than or equal to stats.allocated. This does not include stats.arenas.<i>.pdirty, stats.arenas.<i>.pmuzzy, nor pages
//	entirely devoted to allocator metadata.

void get_jemalloc_stats_active(size_t *value)
{
	size_t size = sizeof(size_t);
	je_mallctl("stats.active", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	size_t value = 1;

	get_jemalloc_stats_active(&value);
	printf("value = %ld 0x%x\n", value, value);

	char *str = je_malloc(40440);
	str[40440-1] = 'A';

	je_mallctl("tcache.flush", NULL, NULL, NULL, 0);

	get_jemalloc_stats_active(&value);
	printf("value = %ld\n", value);
}



