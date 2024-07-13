#include <stdio.h>
#include <jemalloc/jemalloc.h>


//config.fill (bool) r-
//	--enable-fill was specified during build configuration.

void get_jemalloc_config_fill(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("config.fill", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_config_fill(&enable);
	printf("enable = %d\n", enable);
}



