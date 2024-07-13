#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arenas.narenas (unsigned) r-
//	Current limit on number of arenas.

void jemalloc_arena_narenas()
{
	unsigned narenas, i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(narenas);
	je_mallctl("arenas.narenas", &narenas, &len, NULL, 0);
	printf("narenas = %ld.\n", narenas);

}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arena_narenas();
}

