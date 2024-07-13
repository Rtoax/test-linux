#include <stdio.h>
#include <jemalloc/jemalloc.h>

//stats.zero_reallocs (size_t) r- [--enable-stats]
//	Number of times that the realloc() was called with a non-NULL pointer argument and a 0 size argument. This is a
//	fundamentally unsafe pattern in portable programs; see opt.zero_realloc for details.

void get_jemalloc_stats_zero_reallocs(size_t *value) {
	size_t size= sizeof(size_t);
	je_mallctl("stats.zero_reallocs", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	size_t value = 1;

	get_jemalloc_stats_zero_reallocs(&value);
	printf("value = %ld 0x%x\n", value, value);

	char *str = je_malloc(40440);
	str[40440-1] = 'A';

	str = je_realloc(str, 0);
	str = je_realloc(str, 0);

	str[50440-1] = 'A';

	je_mallctl("tcache.flush", NULL, NULL, NULL, 0);

	get_jemalloc_stats_zero_reallocs(&value);
	printf("value = %ld\n", value);
}

