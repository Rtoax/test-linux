#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arena.<i>.destroy (void) --
//	Destroy the arena. Discard all of the arena's extant allocations using the same mechanism as for arena.<i>.reset (
//	with all the same constraints and side effects), merge the arena stats into those accessible at arena index
//	MALLCTL_ARENAS_DESTROYED, and then completely discard all metadata associated with the arena. Future calls to arenas.
//	create may recycle the arena index. Destruction will fail if any threads are currently associated with the arena as a
//	result of calls to thread.arena.

void jemalloc_arena_i_destroy()
{
	unsigned narenas, i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(narenas);
	je_mallctl("arenas.narenas", &narenas, &len, NULL, 0);
	printf("narenas = %ld.\n", narenas);

	miblen = 3;

	je_mallctlnametomib("arena.0.destroy", mib, &miblen);
	for (i = 0; i < narenas; i++) {

		mib[1] = i;
		je_mallctlbymib(mib, miblen, NULL, NULL, NULL, 0);

		/* Do something with initialized... */
		printf("destroy arena %d.\n", i);
	}
}


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
	jemalloc_arena_i_destroy();
	jemalloc_arena_i_initialized();
}




