#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//config.prof (bool) r-
//	--enable-prof was specified during build configuration.

void get_jemalloc_config_prof(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("config.prof", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_config_prof(&enable);
	printf("enable = %d\n", enable);
}


