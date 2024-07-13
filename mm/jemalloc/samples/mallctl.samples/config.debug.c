#include <stdio.h>
#include <jemalloc/jemalloc.h>


//config.debug (bool) r-
//	--enable-debug was specified during build configuration.

void get_jemalloc_config_debug(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("config.debug", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_config_debug(&enable);
	printf("enable = %d\n", enable);
}


