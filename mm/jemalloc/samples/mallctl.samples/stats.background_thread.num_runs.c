#include <stdio.h>
#include <jemalloc/jemalloc.h>

//stats.background_thread.num_runs (uint64_t) r- [--enable-stats]
//	Total number of runs from all background threads.


void get_jemalloc_stats_background_thread_num_runs(size_t *value) {
	size_t size= sizeof(size_t);
	je_mallctl("stats.background_thread.num_runs", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	size_t value = 1;

	get_jemalloc_stats_background_thread_num_runs(&value);
	printf("value = %ld 0x%x\n", value, value);

}




