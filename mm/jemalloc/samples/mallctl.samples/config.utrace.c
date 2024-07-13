#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//config.utrace (bool) r-
//	--enable-utrace was specified during build configuration.

void get_jemalloc_config_utrace(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("config.utrace", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_config_utrace(&enable);
	printf("enable = %d\n", enable);
}

