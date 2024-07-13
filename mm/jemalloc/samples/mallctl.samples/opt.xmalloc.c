#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.utrace (bool) r- [--enable-utrace]
//	Allocation tracing based on utrace(2) enabled/disabled. This option is disabled by default.

void get_jemalloc_opt_utrace(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("opt.utrace", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_utrace(&enable);
	printf("enable = %d\n", enable);
}

