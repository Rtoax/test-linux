#include <stdio.h>
#include <jemalloc/jemalloc.h>

//stats.arenas.<i>.dss (const char *) r-
//	dss (sbrk(2)) allocation precedence as related to mmap(2) allocation. See opt.dss for details.

void jemalloc_arena_narenas(unsigned *pnarenas)
{

	size_t mib[3];
	size_t len, miblen;

	len = sizeof(*pnarenas);
	je_mallctl("arenas.narenas", pnarenas, &len, NULL, 0);
	printf("narenas = %ld.\n", *pnarenas);

}

void jemalloc_stats_arenas_i_dss()
{
	unsigned narenas, i;
	size_t mib[4];
	size_t len, miblen;
	char str_value[32];
	len = 32;

	jemalloc_arena_narenas(&narenas);

	miblen = 4;

	je_mallctlnametomib("stats.arenas.0.dss", mib, &miblen);
	for (i = 0; i < narenas; i++) {

		mib[2] = i;
		je_mallctlbymib(mib, miblen, str_value, &len, NULL, 0);

		/* Do something... */
		printf("stats.arenas.%d.dss = %s ,(%d)\n", i, str_value, len);
	}
}

int main()
{
	unsigned narenas;
	jemalloc_stats_arenas_i_dss();

}


