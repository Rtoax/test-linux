#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arena.<i>.decay (decay 衰减，腐败) (void) --
//	Trigger decay-based purging(purging 净化，清理) of unused dirty/muzzy pages for arena <i>, or for all arenas if <i> equals
//	MALLCTL_ARENAS_ALL. The proportion of unused dirty/muzzy pages to be purged depends on the current time; see opt.
//	dirty_decay_ms and opt.muzy_decay_ms for details.
//	清理脏页，muzzy页，
//
//#!/bin/sh
//
//export MALLOC_CONF="dirty_decay_ms:1000,muzzy_decay_ms:1000,tcache_max:1024"


void jemalloc_arena_i_decay()
{
	unsigned narenas, i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(narenas);
	je_mallctl("arenas.narenas", &narenas, &len, NULL, 0);
	printf("narenas = %ld.\n", narenas);

	miblen = 3;

	je_mallctlnametomib("arena.0.decay", mib, &miblen);
	for (i = 0; i < narenas; i++) {

		mib[1] = i;
		je_mallctlbymib(mib, miblen, NULL, NULL, NULL, 0);

		/* Do something with initialized... */
		printf("decay arena %d's dirty page done.\n", i);
	}
}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arena_i_decay();
}

