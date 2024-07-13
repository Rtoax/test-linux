#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//opt.prof_prefix (const char *) r- [--enable-prof]
//	Filename prefix for profile dumps. If the prefix is set to the empty string, no automatic dumps will occur; this is
//	primarily useful for disabling the automatic final heap dump (which also disables leak reporting, if enabled). The
//	default prefix is jeprof. This prefix value can be overriden by prof.dump_prefix.

void get_jemalloc_opt_prof_prefix(char *value) {
	size_t size = 32;
	je_mallctl("opt.prof_prefix", value, &size, NULL, 0);
	//If set to “alloc”, each byte of uninitialized allocated memory will be initialized to 0xa5.
}


int main(int argc,char **argv)
{
	char value[256] = {"123"};

	get_jemalloc_opt_prof_prefix(value);
	printf("value = %s\n", value);
}
