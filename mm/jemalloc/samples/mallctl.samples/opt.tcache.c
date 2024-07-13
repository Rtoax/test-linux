#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.tcache (bool) r-
//	Thread-specific caching (tcache) enabled/disabled. When there are multiple threads, each thread uses a tcache for
//	objects up to a certain size. Thread-specific caching allows many allocations to be satisfied without performing any
//	thread synchronization, at the cost of increased memory use. See the opt.tcache_max option for related tuning
//	information. This option is enabled by default.

void get_jemalloc_opt_tcache(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("opt.tcache", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_tcache(&enable);
	printf("enable = %d\n", enable);
}


