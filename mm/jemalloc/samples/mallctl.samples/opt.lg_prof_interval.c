#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.lg_prof_interval (ssize_t) r- [--enable-prof]
//	Average interval (log base 2) between memory profile dumps, as measured in bytes of allocation activity. The actual
//	interval between dumps may be sporadic because decentralized allocation counters are used to avoid synchronization
//	bottlenecks. Profiles are dumped to files named according to the pattern <prefix>.<pid>.<seq>.i<iseq>.heap, where <
//	prefix> is controlled by the opt.prof_prefix and prof.dump_prefix options. By default, interval-triggered profile
//	dumping is disabled (encoded as -1).

void get_jemalloc_opt_lg_prof_interval(ssize_t *value) {
	size_t size = sizeof(ssize_t);
	je_mallctl("opt.lg_prof_interval", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	ssize_t value = 0;

	get_jemalloc_opt_lg_prof_interval(&value);

	//By default, interval-triggered stats output is disabled (encoded as -1).
	printf("value = %ld\n", value);
}






