#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arenas.tcache_max (size_t) r-
//	Maximum thread-cached size class.

void jemalloc_arena_tcache_max()
{
	size_t tcache_max;
		int i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(tcache_max);
	je_mallctl("arenas.tcache_max", &tcache_max, &len, NULL, 0);
	printf("tcache_max = %ld.\n", tcache_max);

}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arena_tcache_max();
}