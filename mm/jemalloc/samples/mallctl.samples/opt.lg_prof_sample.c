#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.lg_prof_sample (size_t) r- [--enable-prof]
//	Average interval (log base 2) between allocation samples, as measured in bytes of allocation activity. Increasing the
//	sampling interval decreases profile fidelity, but also decreases the computational overhead. The default sample
//	interval is 512 KiB (2^19 B).


void get_jemalloc_opt_lg_prof_sample(size_t *value) {
	size_t size = sizeof(size_t);
	je_mallctl("opt.lg_prof_sample", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	size_t value = true;

	get_jemalloc_opt_lg_prof_sample(&value);

//	The default sample
//	interval is 512 KiB (2^19 B).
	printf("enable = %d\n", value);
}

