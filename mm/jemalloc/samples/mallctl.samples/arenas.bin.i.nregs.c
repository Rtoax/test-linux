#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arenas.bin.<i>.nregs (uint32_t) r-
//	Number of regions per slab.


void jemalloc_arenas_bin_i_nregs()
{
	unsigned nbins, i;
	size_t mib[4];
	size_t len, miblen;

	len = sizeof(nbins);
	je_mallctl("arenas.nbins", &nbins, &len, NULL, 0);

	miblen = 4;
	je_mallctlnametomib("arenas.bin.0.nregs", mib, &miblen);
	for (i = 0; i < nbins; i++) {
		uint32_t nregs;

		mib[2] = i;
		len = sizeof(nregs);
		je_mallctlbymib(mib, miblen, (void *)&nregs, &len, NULL, 0);
		/* Do something with bin_size... */
		printf("nregs = %d\n", nregs);
	}
}


int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arenas_bin_i_nregs();
}


