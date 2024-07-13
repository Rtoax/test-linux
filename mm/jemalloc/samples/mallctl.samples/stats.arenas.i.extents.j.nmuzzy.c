#include <stdio.h>
#include <jemalloc/jemalloc.h>

//stats.arenas.<i>.extents.<j>.n{extent_type} (size_t) r- [--enable-stats]
//	Number of extents of the given type in this arena in the bucket corresponding to page size index <j>. The extent type
//	is one of dirty, muzzy, or retained.

void jemalloc_arena_narenas(unsigned *pnarenas)
{
	size_t len;

	len = sizeof(*pnarenas);
	je_mallctl("arenas.narenas", pnarenas, &len, NULL, 0);
//	printf("narenas = %ld.\n", *pnarenas);

}

void jemalloc_stats_arenas_i_extent_avail(unsigned iarenas, size_t *pextent_avail)
{
	size_t mib[4];
	size_t len, miblen;

	len = 32;
	miblen = 4;

	je_mallctlnametomib("stats.arenas.0.extent_avail", mib, &miblen);

	mib[2] = iarenas;
	je_mallctlbymib(mib, miblen, pextent_avail, &len, NULL, 0);

	/* Do something... */
//	printf("stats.arenas.%d.extent_avail = %d ,(%d)\n", i, *pextent_avail, len);
}



void jemalloc_stats_arenas_i_extents_j_nmuzzy()
{
	unsigned narenas, i, j;

	size_t mib[6];
	size_t len, miblen;
	size_t value;

	len = 32;

	jemalloc_arena_narenas(&narenas);

	miblen = 6;

	je_mallctlnametomib("stats.arenas.0.extents.0.nmuzzy", mib, &miblen);
	for (i = 0; i < narenas; i++) {
		size_t extent_avail;
		jemalloc_stats_arenas_i_extent_avail(i, &extent_avail);
		for (j = 0; j < extent_avail; j++) {

			len = 32; //检测返回的结果是不是 8

			mib[2] = i;
			mib[4] = j;

			je_mallctlbymib(mib, miblen, &value, &len, NULL, 0);

			/* Do something... */
			printf("stats.arenas.%d.extents.%d.nmuzzy = %d bytes,(%d)\n", i, j, value, len);
		}
	}
}


void jemalloc_test()
{
	char *str1 = je_malloc(1234);
	int i;
	for(i=0;i<1024;i++) {
		str1 = je_malloc(1024);
	}

}


int main()
{
	unsigned narenas;
	jemalloc_test();
	jemalloc_stats_arenas_i_extents_j_nmuzzy();

}



