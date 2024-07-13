#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.prof_accum (bool) r- [--enable-prof]
//	Reporting of cumulative(积累的，聚集的) object/byte counts in profile dumps enabled/disabled. If this option is enabled, every unique
//	backtrace must be stored for the duration of execution. Depending on the application, this can impose a large memory
//	overhead, and the cumulative counts are not always of interest. This option is disabled by default.


void get_jemalloc_opt_prof_accum(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("opt.prof_accum", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_prof_accum(&enable);
	printf("enable = %d\n", enable);
}





