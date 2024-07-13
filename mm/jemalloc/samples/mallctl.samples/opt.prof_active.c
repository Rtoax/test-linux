#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.prof_active (bool) r- [--enable-prof] 简明扼要
//	Profiling activated/deactivated. This is a secondary control mechanism that makes it possible to start the
//	application with profiling enabled (see the opt.prof option) but inactive, then toggle profiling at any time during
//	program execution with the prof.active mallctl. This option is enabled by default.


void get_jemalloc_opt_prof_active(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("opt.prof_active", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_prof_active(&enable);
	printf("enable = %d\n", enable);
}




