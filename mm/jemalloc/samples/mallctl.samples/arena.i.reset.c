#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arena.<i>.reset (void) --
//	Discard all of the arena's extant allocations. This interface can only be used with arenas explicitly created via
//	arenas.create. None of the arena's discarded/cached allocations may accessed afterward. As part of this requirement,
//	all thread caches which were used to allocate/deallocate in conjunction with the arena must be flushed beforehand.

void jemalloc_arena_i_reset()
{
	unsigned narenas, i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(narenas);
	je_mallctl("arenas.narenas", &narenas, &len, NULL, 0);
	printf("narenas = %ld.\n", narenas);

	miblen = 3;

	je_mallctlnametomib("arena.0.reset", mib, &miblen);
	for (i = 0; i < narenas; i++) {

		mib[1] = i;
		je_mallctlbymib(mib, miblen, NULL, NULL, NULL, 0);

		/* Do something with initialized... */
		printf("reset arena %d.\n", i);
	}
}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arena_i_reset();
}



