#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arenas.nbins (unsigned) r-
//	Number of bin size classes.

void jemalloc_arenas_nbins()
{
	unsigned nbins;
		int i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(nbins);
	je_mallctl("arenas.nbins", &nbins, &len, NULL, 0);
	printf("nbins = %d.\n", nbins);

}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arenas_nbins();
}

