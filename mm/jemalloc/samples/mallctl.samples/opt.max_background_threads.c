#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.max_background_threads (size_t) r-
//	Maximum number of background threads that will be created if background_thread is set. Defaults to number of cpus.


void get_jemalloc_opt_max_background_threads(size_t *value) {
	size_t size = sizeof(size_t);
	je_mallctl("opt.max_background_threads", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	size_t value = 0;

	get_jemalloc_opt_max_background_threads(&value);
	printf("value = %ld\n", value);
}


