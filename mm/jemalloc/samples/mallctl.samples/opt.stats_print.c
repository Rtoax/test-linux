#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.stats_print (bool) r-
//	Enable/disable statistics printing at exit. If enabled, the malloc_stats_print() function is called at program exit
//	via an atexit(3) function. opt.stats_print_opts can be combined to specify output options. If --enable-stats is
//	specified during configuration, this has the potential to cause deadlock for a multi-threaded process that exits
//	while one or more threads are executing in the memory allocation functions. Furthermore, atexit() may allocate memory
//	during application initialization and then deadlock internally when jemalloc in turn calls atexit(), so this option
//	is not universally usable (though the application can register its own atexit() function with equivalent functionality
//	). Therefore, this option should only be used with care; it is primarily intended as a performance tuning aid during
//	application development. This option is disabled by default.


void get_jemalloc_opt_stats_print(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("opt.stats_print", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_stats_print(&enable);
	printf("enable = %d\n", enable);
}


