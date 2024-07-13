#include <stdio.h>
#include <jemalloc/jemalloc.h>

//stats.mutexes.reset (void) -- [--enable-stats]
//	Reset all mutex profile statistics, including global mutexes, arena mutexes and bin mutexes.

void get_jemalloc_stats_mutexes_reset()
{
	je_mallctl("stats.mutexes.reset", NULL, NULL, NULL, 0);
}

int main(int argc,char **argv)
{
	get_jemalloc_stats_mutexes_reset();
}


