#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.stats_interval (int64_t) r-
//	Average interval between statistics outputs, as measured in bytes of allocation activity. The actual interval may be
//	sporadic because decentralized event counters are used to avoid synchronization bottlenecks. The output may be
//	triggered on any thread, which then calls malloc_stats_print(). opt.stats_interval_opts can be combined to specify
//	output options. By default, interval-triggered stats output is disabled (encoded as -1).

void get_jemalloc_opt_stats_interval(int64_t *value) {
	size_t size = sizeof(int64_t);
	je_mallctl("opt.stats_interval", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	int64_t value = 0;

	get_jemalloc_opt_stats_interval(&value);

	//By default, interval-triggered stats output is disabled (encoded as -1).
	printf("value = %ld\n", value);
}





