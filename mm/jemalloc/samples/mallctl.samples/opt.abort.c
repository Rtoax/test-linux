#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//opt.abort (bool) r-
//	Abort-on-warning enabled/disabled. If true, most warnings are fatal. Note that runtime option warnings are not
//	included (see opt.abort_conf for that). The process will call abort(3) in these cases. This option is disabled by
//	default unless --enable-debug is specified during configuration, in which case it is enabled by default.
//	abort功能


void get_jemalloc_opt_abort(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("opt.abort", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_abort(&enable);
	printf("enable = %d\n", enable);
}



