#include <stdio.h>
#include <jemalloc/jemalloc.h>

//stats.background_thread.run_interval (uint64_t) r- [--enable-stats]
//	Average run interval in nanoseconds of background threads.


void get_jemalloc_stats_background_thread_run_interval(size_t *value) {
	size_t size= sizeof(size_t);
	je_mallctl("stats.background_thread.run_interval", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	size_t value = 1;

	get_jemalloc_stats_background_thread_run_interval(&value);
	printf("value = %ld nanoseconds\n", value);

}





