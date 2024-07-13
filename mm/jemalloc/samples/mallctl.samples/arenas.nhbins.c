#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arenas.nhbins (unsigned) r-
//	Total number of thread cache bin size classes.


void jemalloc_arenas_nhbins()
{
	unsigned nhbins;
		int i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(nhbins);
	je_mallctl("arenas.nhbins", &nhbins, &len, NULL, 0);
	printf("nhbins = %d.\n", nhbins);

}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arenas_nhbins();
}


