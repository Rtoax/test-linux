#include <stdio.h>
#include <jemalloc/jemalloc.h>

//stats.arenas.<i>.dirty_decay_ms (ssize_t) r-
//	Approximate time in milliseconds from the creation of a set of unused dirty pages until an equivalent set of unused
//	dirty pages is purged and/or reused. See opt.dirty_decay_ms for details.

void jemalloc_arena_narenas(unsigned *pnarenas)
{

	size_t mib[3];
	size_t len, miblen;

	len = sizeof(*pnarenas);
	je_mallctl("arenas.narenas", pnarenas, &len, NULL, 0);
	printf("narenas = %ld.\n", *pnarenas);

}

void jemalloc_stats_arenas_i_dirty_decay_ms()
{
	unsigned narenas, i;
	size_t mib[4];
	size_t len, miblen;
	ssize_t value;
	len = 32;

	jemalloc_arena_narenas(&narenas);

	miblen = 4;

	je_mallctlnametomib("stats.arenas.0.dirty_decay_ms", mib, &miblen);
	for (i = 0; i < narenas; i++) {

		mib[2] = i;
		je_mallctlbymib(mib, miblen, &value, &len, NULL, 0);

		/* Do something... */
		printf("stats.arenas.%d.dirty_decay_ms = %d milliseconds,(%d)\n", i, value, len);
	}
}

int main()
{
	unsigned narenas;
	jemalloc_stats_arenas_i_dirty_decay_ms();

}



