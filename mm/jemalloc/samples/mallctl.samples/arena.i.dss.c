#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arena.<i>.dss (const char *) rw
//	Set the precedence of dss allocation as related to mmap allocation for arena <i>, or for all arenas if <i> equals
//	MALLCTL_ARENAS_ALL. See opt.dss for supported settings.


void jemalloc_arena_i_dss()
{
	unsigned narenas, i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(narenas);
	je_mallctl("arenas.narenas", &narenas, &len, NULL, 0);
	printf("narenas = %ld.\n", narenas);

	miblen = 3;

	je_mallctlnametomib("arena.0.dss", mib, &miblen);
	for (i = 0; i < narenas; i++) {
		char dss[256];

		mib[1] = i;
		len = sizeof(dss);
		je_mallctlbymib(mib, miblen, NULL, NULL, "dss", 3); //不起作用
		je_mallctlbymib(mib, miblen, (void *)dss, &len, NULL, 0);

		printf("dss = %s\n", dss);
	}
}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arena_i_dss();
}

