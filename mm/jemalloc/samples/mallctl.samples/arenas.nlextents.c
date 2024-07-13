#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arenas.nlextents (unsigned) r-
//	Total number of large size classes.

void jemalloc_arenas_nlextents()
{
	unsigned nlextents;
		int i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(nlextents);
	je_mallctl("arenas.nlextents", &nlextents, &len, NULL, 0);
	printf("nlextents = %d.\n", nlextents);

}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arenas_nlextents();
}



