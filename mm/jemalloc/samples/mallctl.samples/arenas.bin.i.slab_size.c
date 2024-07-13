#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arenas.bin.<i>.slab_size (size_t) r-
//	Number of bytes per slab.


void jemalloc_arenas_bin_i_slab_size()
{
	unsigned nbins, i;
	size_t mib[4];
	size_t len, miblen;

	len = sizeof(nbins);
	je_mallctl("arenas.nbins", &nbins, &len, NULL, 0);

	miblen = 4;
	je_mallctlnametomib("arenas.bin.0.slab_size", mib, &miblen);
	for (i = 0; i < nbins; i++) {
		size_t slab_size;

		mib[2] = i;
		len = sizeof(slab_size);
		je_mallctlbymib(mib, miblen, (void *)&slab_size, &len, NULL, 0);
		/* Do something with slab_size... */
		printf("slab_size = %d\n", slab_size);
	}
}


int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arenas_bin_i_slab_size();
}



