#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arena.<i>.initialized (bool) r-
//	Get whether the specified arena's statistics are initialized (i.e. the arena was initialized prior to the current
//	epoch). This interface can also be nominally used to query whether the merged statistics corresponding to
//	MALLCTL_ARENAS_ALL are initialized (always true).
//	是否已经初始化过



void jemalloc_arena_i_initialized()
{
	unsigned narenas, i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(narenas);
	je_mallctl("arenas.narenas", &narenas, &len, NULL, 0);
	printf("narenas = %ld.\n", narenas);

	miblen = 3;

	je_mallctlnametomib("arena.0.initialized", mib, &miblen);
	for (i = 0; i < narenas; i++) {
		bool initialized;

		mib[1] = i;
		len = sizeof(initialized);
		je_mallctlbymib(mib, miblen, (void *)&initialized, &len, NULL, 0);

		/* Do something with initialized... */
		printf("initialized = %d\n", initialized);
	}
}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arena_i_initialized();
}
