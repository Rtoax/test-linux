#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arena.<i>.retain_grow_limit (size_t) rw
//	Maximum size to grow retained region (only relevant when opt.retain is enabled). This controls the maximum increment
//	to expand virtual memory, or allocation through arena.<i>extent_hooks. In particular, if customized extent hooks
//	reserve physical memory (e.g. 1G huge pages), this is useful to control the allocation hook's input size. The default
//	is no limit.

void jemalloc_arena_i_retain_grow_limit()
{
	unsigned narenas, i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(narenas);
	je_mallctl("arenas.narenas", &narenas, &len, NULL, 0);
	printf("narenas = %ld.\n", narenas);

	miblen = 3;

	je_mallctlnametomib("arena.0.retain_grow_limit", mib, &miblen);
	for (i = 0; i < narenas; i++) {
		size_t retain_grow_limit = 0;

		mib[1] = i;
		len = sizeof(retain_grow_limit);
		je_mallctlbymib(mib, miblen, (void *)&retain_grow_limit, &len, NULL, 0);
		printf("retain_grow_limit = %ld,%ld,%ld,%ld,%ld,%ld,%ld,\n",
														 retain_grow_limit,
														 retain_grow_limit/1024,
														 retain_grow_limit/1024/1024,
														 retain_grow_limit/1024/1024/1024,
														 retain_grow_limit/1024/1024/1024/1024,
														 retain_grow_limit/1024/1024/1024/1024/1024,
														 retain_grow_limit/1024/1024/1024/1024/1024/1024);
//		printf("retain_grow_limit = %ld \n", retain_grow_limit);

		retain_grow_limit += 1024;

		je_mallctlbymib(mib, miblen, NULL, NULL, (void *)&retain_grow_limit, sizeof(retain_grow_limit));
//		printf("retain_grow_limit = %x \n", retain_grow_limit);
		printf("retain_grow_limit = %ld,%ld,%ld,%ld,%ld,%ld,%ld,\n",
														 retain_grow_limit,
														 retain_grow_limit/1024,
														 retain_grow_limit/1024/1024,
														 retain_grow_limit/1024/1024/1024,
														 retain_grow_limit/1024/1024/1024/1024,
														 retain_grow_limit/1024/1024/1024/1024/1024,
														 retain_grow_limit/1024/1024/1024/1024/1024/1024);
	}
}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arena_i_retain_grow_limit();
}




