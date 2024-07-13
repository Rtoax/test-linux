#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arenas.dirty_decay_ms (ssize_t) rw
//	Current default per-arena approximate time in milliseconds from the creation of a set of unused dirty pages until an
//	equivalent set of unused dirty pages is purged and/or reused, used to initialize arena.<i>.dirty_decay_ms during
//	arena creation. See opt.dirty_decay_ms for additional information.

void jemalloc_arena_dirty_decay_ms()
{
	ssize_t dirty_decay_ms;

	unsigned i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(dirty_decay_ms);
	je_mallctl("arenas.dirty_decay_ms", &dirty_decay_ms, &len, NULL, 0);
	printf("dirty_decay_ms = %ld.\n", dirty_decay_ms);

	dirty_decay_ms*=2;

	je_mallctl("arenas.dirty_decay_ms", NULL, 0, &dirty_decay_ms, len);

	je_mallctl("arenas.dirty_decay_ms", &dirty_decay_ms, &len, NULL, 0);
	printf("dirty_decay_ms = %ld.\n", dirty_decay_ms);

}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arena_dirty_decay_ms();
}


