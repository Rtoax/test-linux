#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//config.prof_libgcc (bool) r-
//--disable-prof-libgcc was not specified during build configuration.


void get_jemalloc_config_prof_libgcc(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("config.prof_libgcc", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_config_prof_libgcc(&enable);
	printf("enable = %d\n", enable);
}



