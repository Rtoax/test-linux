#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arena.<i>.muzzy_decay_ms (ssize_t) rw
//	Current per-arena approximate time in milliseconds from the creation of a set of unused muzzy pages until an
//	equivalent set of unused muzzy pages is purged and/or reused. Each time this interface is set, all currently unused
//	muzzy pages are considered to have fully decayed, which causes immediate purging of all unused muzzy pages unless the
//	decay time is set to -1 (i.e. purging disabled). See opt.muzzy_decay_ms for additional information.

void jemalloc_arena_i_muzzy_decay_ms()
{
	unsigned narenas, i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(narenas);
	je_mallctl("arenas.narenas", &narenas, &len, NULL, 0);
	printf("narenas = %ld.\n", narenas);

	miblen = 3;

	je_mallctlnametomib("arena.0.muzzy_decay_ms", mib, &miblen);
	for (i = 0; i < narenas; i++) {
		ssize_t muzzy_decay_ms = 10;

		mib[1] = i;
		len = sizeof(muzzy_decay_ms);
		je_mallctlbymib(mib, miblen, (void *)&muzzy_decay_ms, &len, NULL, 0);
		printf("muzzy_decay_ms = %ld milliseconds\n", muzzy_decay_ms);

		muzzy_decay_ms *= 2;

		je_mallctlbymib(mib, miblen, NULL, NULL, (void *)&muzzy_decay_ms, sizeof(muzzy_decay_ms));
		printf("muzzy_decay_ms = %ld milliseconds\n", muzzy_decay_ms);
	}
}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arena_i_muzzy_decay_ms();
}



