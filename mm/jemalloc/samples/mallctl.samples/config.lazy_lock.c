#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//config.lazy_lock (bool) r-
//	--enable-lazy-lock was specified during build configuration.

void get_jemalloc_config_lazy_lock(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("config.lazy_lock", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_config_lazy_lock(&enable);
	printf("enable = %d\n", enable);
}

