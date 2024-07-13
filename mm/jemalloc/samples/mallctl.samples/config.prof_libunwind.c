#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//config.prof_libunwind (bool) r-
//	--enable-prof-libunwind was specified during build configuration.

void get_jemalloc_config_prof_libunwind(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("config.prof_libunwind", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_config_prof_libunwind(&enable);
	printf("enable = %d\n", enable);
}




