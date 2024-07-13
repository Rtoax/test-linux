#include <stdio.h>
#include <jemalloc/jemalloc.h>

//stats.arenas.<i>.resident (size_t) r- [--enable-stats]
//	Maximum number of bytes in physically resident data pages mapped by the arena, comprising all pages dedicated to
//	allocator metadata, pages backing active allocations, and unused dirty pages. This is a maximum rather than precise
//	because pages may not actually be physically resident if they correspond to demand-zeroed virtual memory that has not
//	yet been touched. This is a multiple of the page size.

void jemalloc_arena_narenas(unsigned *pnarenas)
{

	size_t mib[3];
	size_t len, miblen;

	len = sizeof(*pnarenas);
	je_mallctl("arenas.narenas", pnarenas, &len, NULL, 0);
	printf("narenas = %ld.\n", *pnarenas);

}

void jemalloc_stats_arenas_i_resident()
{
	unsigned narenas, i;
	size_t mib[4];
	size_t len, miblen;
	size_t value;
	len = 32;

	jemalloc_arena_narenas(&narenas);

	miblen = 4;

	je_mallctlnametomib("stats.arenas.0.resident", mib, &miblen);
	for (i = 0; i < narenas; i++) {

		mib[2] = i;
		je_mallctlbymib(mib, miblen, &value, &len, NULL, 0);

		/* Do something... */
		printf("stats.arenas.%d.resident = %d bytes %d Mbytes,(%d)\n", i, value, value/1024, len);
	}
}

int main()
{
	unsigned narenas;
	jemalloc_stats_arenas_i_resident();

}






