#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.prof_final (bool) r- [--enable-prof]
//	Use an atexit(3) function to dump final memory usage to a file named according to the pattern <prefix>.<pid>.<seq>.f.
//	heap, where <prefix> is controlled by the opt.prof_prefix and prof.dump_prefix options. Note that atexit() may
//	allocate memory during application initialization and then deadlock internally when jemalloc in turn calls atexit(),
//	so this option is not universally usable (though the application can register its own atexit() function with
//	equivalent functionality). This option is disabled by default.

void get_jemalloc_opt_prof_final(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("opt.prof_final", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_prof_final(&enable);
	printf("enable = %d\n", enable);
}

