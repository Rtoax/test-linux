#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arenas.bin.<i>.size (size_t) r-
//	Maximum size supported by size class.


void jemalloc_arenas_bin_i_size()
{
	unsigned nbins, i;
	size_t mib[4];
	size_t len, miblen;

	len = sizeof(nbins);
	je_mallctl("arenas.nbins", &nbins, &len, NULL, 0);

	miblen = 4;
	je_mallctlnametomib("arenas.bin.0.size", mib, &miblen);
	for (i = 0; i < nbins; i++) {
		size_t bin_size;

		mib[2] = i;
		len = sizeof(bin_size);
		je_mallctlbymib(mib, miblen, (void *)&bin_size, &len, NULL, 0);
		/* Do something with bin_size... */
		printf("bin_size = %d\n", bin_size);
	}
}


int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arenas_bin_i_size();
}

