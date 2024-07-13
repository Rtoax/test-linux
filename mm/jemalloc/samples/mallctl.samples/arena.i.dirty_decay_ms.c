#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arena.<i>.dirty_decay_ms (ssize_t) rw
//	Current per-arena approximate time in milliseconds from the creation of a set of unused dirty pages until an
//	equivalent set of unused dirty pages is purged and/or reused. Each time this interface is set, all currently unused
//	dirty pages are considered to have fully decayed, which causes immediate purging of all unused dirty pages unless the
//	decay time is set to -1 (i.e. purging disabled). See opt.dirty_decay_ms for additional information.

void jemalloc_arena_i_dirty_decay_ms()
{
	unsigned narenas, i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(narenas);
	je_mallctl("arenas.narenas", &narenas, &len, NULL, 0);
	printf("narenas = %ld.\n", narenas);

	miblen = 3;

	je_mallctlnametomib("arena.0.dirty_decay_ms", mib, &miblen);
	for (i = 0; i < narenas; i++) {
		ssize_t dirty_decay_ms = 0;

		mib[1] = i;
		len = sizeof(dirty_decay_ms);
		je_mallctlbymib(mib, miblen, (void *)&dirty_decay_ms, &len, NULL, 0);
		printf("dirty_decay_ms = %ld milliseconds\n", dirty_decay_ms);

		dirty_decay_ms *= 2;

		je_mallctlbymib(mib, miblen, NULL, NULL, (void *)&dirty_decay_ms, sizeof(dirty_decay_ms));
		printf("dirty_decay_ms = %ld milliseconds\n", dirty_decay_ms);
	}
}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arena_i_dirty_decay_ms();
}


