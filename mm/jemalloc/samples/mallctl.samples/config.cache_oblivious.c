#include <stdio.h>
#include <jemalloc/jemalloc.h>


//config.cache_oblivious (bool) r- 不知道、未察觉、未注意
//--------------------------------------------------------------------------------------------------------------------
//	--enable-cache-oblivious was specified during build configuration.

void get_jemalloc_config_cache_oblivious(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("config.cache_oblivious", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_config_cache_oblivious(&enable);
	printf("enable = %d\n", enable);
}

