#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//opt.zero_realloc (const char *) r-
//	Determines the behavior of realloc() when passed a value of zero for the new size. “strict” treats this as an
//	allocation of size zero (and returns a non-null result except in case of resource exhaustion). “free” treats this
//	as a deallocation of the pointer, and returns NULL without setting errno. “abort” aborts the process if zero is
//	passed. The default is “strict”.

void get_jemalloc_opt_zero_realloc(char *value) {
	size_t size = 32;
	je_mallctl("opt.zero_realloc", value, &size, NULL, 0);
	//If set to “alloc”, each byte of uninitialized allocated memory will be initialized to 0xa5.
}


int main(int argc,char **argv)
{
	char value[256] = {"123"};

	get_jemalloc_opt_zero_realloc(value);
	printf("value = %s\n", value);
}

