#include <stdio.h>
#include <jemalloc/jemalloc.h>

//prof.interval (uint64_t) r- [--enable-prof]
//	Average number of bytes allocated between interval-based profile dumps. See the opt.lg_prof_interval option for
//	additional information.

void get_jemalloc_prof_interval(uint64_t *value) {
	size_t size= sizeof(uint64_t);
	je_mallctl("prof.interval", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	uint64_t value = 1;

	get_jemalloc_prof_interval(&value);

	printf("value = %ld\n", value);
}

