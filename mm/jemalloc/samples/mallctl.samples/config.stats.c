#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//config.stats (bool) r-
//	--enable-stats was specified during build configuration.

void get_jemalloc_config_stats(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("config.stats", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_config_stats(&enable);
	printf("enable = %d\n", enable);
}





