#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"


//config.malloc_conf (const char *) r-
//	Embedded configure-time-specified run-time options string, empty unless --with-malloc-conf was specified during build
//	configuration.
//	嵌入特殊的配置时间， 需要在编译jemalloc时指定 --with-malloc-conf

void get_jemalloc_config_malloc_conf(char *value) {
	size_t size = sizeof(bool);
	je_mallctl("config.malloc_conf", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	char value[256] = {"123"};

	get_jemalloc_config_malloc_conf(value);
	printf("value = %s\n", value);
}


