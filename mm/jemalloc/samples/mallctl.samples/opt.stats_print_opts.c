#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//opt.stats_print_opts (const char *) r-
//	Options (the opts string) to pass to the malloc_stats_print() at exit (enabled through opt.stats_print). See
//	available options in malloc_stats_print(). Has no effect unless opt.stats_print is enabled. The default is “”.


void get_jemalloc_opt_stats_print_opts(char *value) {
	size_t size = 32;
	je_mallctl("opt.stats_print_opts", value, &size, NULL, 0);
}


int main(int argc,char **argv)
{
	char value[256] = {"123"};

	get_jemalloc_opt_stats_print_opts(value);
	printf("value = %s\n", value);
}



