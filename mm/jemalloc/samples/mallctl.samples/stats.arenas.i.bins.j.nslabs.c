#include <stdio.h>
#include <jemalloc/jemalloc.h>


//stats.arenas.<i>.bins.<j>.nslabs (uint64_t) r- [--enable-stats]
//	Cumulative number of slabs created.

void jemalloc_arena_narenas(unsigned *pnarenas)
{
	size_t len;

	len = sizeof(*pnarenas);
	je_mallctl("arenas.narenas", pnarenas, &len, NULL, 0);
	printf("narenas = %ld.\n", *pnarenas);

}

void jemalloc_arenas_nbins(unsigned *pnbins)
{
	size_t len;

	len = sizeof(*pnbins);
	je_mallctl("arenas.nbins", pnbins, &len, NULL, 0);
	printf("arenas.nbins = %d.\n", *pnbins);

}


void jemalloc_stats_arenas_i_bins_j_nslabs()
{
	unsigned narenas, i, j;
	unsigned nbins;

	size_t mib[6];
	size_t len, miblen;
	uint64_t value;

	len = 32;

	jemalloc_arena_narenas(&narenas);
	jemalloc_arenas_nbins(&nbins);

	miblen = 6;

	je_mallctlnametomib("stats.arenas.0.bins.0.nslabs", mib, &miblen);
	for (i = 0; i < narenas; i++) {
		for (j = 0; j < nbins; j++) {

			len = 32; //检测返回的结果是不是 8

			mib[2] = i;
			mib[4] = j;

			je_mallctlbymib(mib, miblen, &value, &len, NULL, 0);

			/* Do something... */
			printf("stats.arenas.%d.bins.%d.nslabs = %d bytes,(%d)\n", i, j, value, len);
		}
	}
}


void jemalloc_test()
{
	char *str1 = je_malloc(1234);
	char *str2 = je_malloc(12121234);
	char *str3 = je_malloc(1234);
}


int main()
{
	unsigned narenas;
	jemalloc_test();
	jemalloc_stats_arenas_i_bins_j_nslabs();

}
