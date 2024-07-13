#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//config.xmalloc (bool) r-
//	--enable-xmalloc was specified during build configuration.

void get_jemalloc_config_xmalloc(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("config.xmalloc", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_config_xmalloc(&enable);
	printf("enable = %d\n", enable);
}


