#include <stdio.h>
#include <jemalloc/jemalloc.h>

int main(void)
{
	unsigned nbins, i;
	size_t mib[4];
	size_t len, miblen;

	len = sizeof(nbins);
	mallctl("arenas.nbins", &nbins, &len, NULL, 0);

	miblen = 4;
	mallctlnametomib("arenas.bin.0.size", mib, &miblen);
	for (i = 0; i < nbins; i++) {
		size_t bin_size;

		mib[2] = i;
		len = sizeof(bin_size);
		mallctlbymib(mib, miblen, (void *)&bin_size, &len, NULL, 0);
		/* Do something with bin_size... */
		printf("bin_size = %ld\n", bin_size);
	}
	return 0;
}
