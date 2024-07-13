#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//opt.narenas (unsigned) r-
//	Maximum number of arenas to use for automatic multiplexing of threads and arenas. The default is four times the
//	number of CPUs, or one if there is a single CPU.

void get_jemalloc_opt_narenas(unsigned *value) {
	size_t size = 4;
	je_mallctl("opt.narenas", value, &size, NULL, 0);
}


int main(int argc,char **argv)
{
	unsigned value = 0;

	get_jemalloc_opt_narenas(&value);
	printf("value = %d\n", value);
}

