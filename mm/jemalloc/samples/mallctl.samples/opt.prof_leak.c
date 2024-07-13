#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.prof_leak (bool) r- [--enable-prof]
//	Leak reporting enabled/disabled. If enabled, use an atexit(3) function to report memory leaks detected by allocation
//	sampling. See the opt.prof option for information on analyzing heap profile output. This option is disabled by default.

void get_jemalloc_opt_prof_leak(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("opt.prof_leak", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_prof_leak(&enable);
	printf("enable = %d\n", enable);
}


