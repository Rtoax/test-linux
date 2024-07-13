#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arenas.nlextents (unsigned) r-
//	Total number of large size classes.
//arenas.lextent.<i>.size (size_t) r-
//	Maximum size supported by this large size class.


void jemalloc_arenas_lextent_i_size()
{
	unsigned nlextents;
	int i;
	size_t mib[4];
	size_t len, miblen;

	len = sizeof(nlextents);
	je_mallctl("arenas.nlextents", &nlextents, &len, NULL, 0);

	miblen = 4;
	je_mallctlnametomib("arenas.lextent.0.size", mib, &miblen);
	for (i = 0; i < nlextents; i++) {
		size_t size;

		mib[2] = i;
		len = sizeof(size);
		je_mallctlbymib(mib, miblen, (void *)&size, &len, NULL, 0);
		/* Do something with size... */
		printf("size = %ld, %016x\n", size, (unsigned long int)size);
	}
}


int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arenas_lextent_i_size();
}


