#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

void get_jemalloc_config_malloc_conf(char *value)
{
	size_t size = sizeof(bool);
	je_mallctl("config.malloc_conf", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	char value[256] = {"123"};

	get_jemalloc_config_malloc_conf(value);
	printf("value = %s\n", value);

	return 0;
}


