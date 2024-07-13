#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//opt.abort_conf (bool) r-
//	Abort-on-invalid-configuration enabled/disabled. If true, invalid runtime options are fatal. The process will call
//	abort(3) in these cases. This option is disabled by default unless --enable-debug is specified during configuration,
//	in which case it is enabled by default.


void get_jemalloc_opt_abort_conf(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("opt.abort_conf", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_abort_conf(&enable);
	printf("enable = %d\n", enable);
}





