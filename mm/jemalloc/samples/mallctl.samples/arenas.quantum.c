#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arenas.quantum (size_t) r-
//	Quantum size. 量子大小？

void jemalloc_arena_quantum()
{
	size_t quantum;
		int i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(quantum);
	je_mallctl("arenas.quantum", &quantum, &len, NULL, 0);
	printf("quantum = %ld.\n", quantum);

}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arena_quantum();
}


