#include <stdio.h>
#include <jemalloc/jemalloc.h>

//prof.lg_sample (size_t) r- [--enable-prof]
//	Get the current sample rate (see opt.lg_prof_sample).

void get_jemalloc_prof_lg_sample(size_t *value) {
	size_t size= sizeof(size_t);
	je_mallctl("prof.lg_sample", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	size_t value = 1;

	get_jemalloc_prof_lg_sample(&value);

	printf("value = %ld\n", value);
}
