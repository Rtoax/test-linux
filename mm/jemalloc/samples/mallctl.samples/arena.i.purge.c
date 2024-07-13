#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arena.<i>.purge(purging 净化，清理) (void) --
//	Purge all unused dirty pages for arena <i>, or for all arenas if <i> equals MALLCTL_ARENAS_ALL.


void jemalloc_arena_i_purge()
{
	unsigned narenas, i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(narenas);
	je_mallctl("arenas.narenas", &narenas, &len, NULL, 0);
	printf("narenas = %ld.\n", narenas);

	miblen = 3;

	je_mallctlnametomib("arena.0.purge", mib, &miblen);
	for (i = 0; i < narenas; i++) {

		mib[1] = i;
		je_mallctlbymib(mib, miblen, NULL, NULL, NULL, 0);

		/* Do something with initialized... */
		printf("purge arena %d's dirty page done.\n", i);
	}
}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arena_i_purge();
}


