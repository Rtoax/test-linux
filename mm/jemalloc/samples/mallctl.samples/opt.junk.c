#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//opt.junk (const char *) r- [--enable-fill]
//	Junk filling. If set to “alloc”, each byte of uninitialized allocated memory will be initialized to 0xa5. If set
//	to “free”, all deallocated memory will be initialized to 0x5a. If set to “true”, both allocated and
//	deallocated memory will be initialized, and if set to “false”, junk filling be disabled entirely. This is
//	intended for debugging and will impact performance negatively. This option is “false” by default unless --enable-
//	debug is specified during configuration, in which case it is “true” by default.


void get_jemalloc_opt_junk(char *value) {
	size_t size = 32;
	je_mallctl("opt.junk", value, &size, NULL, 0);
	//If set to “alloc”, each byte of uninitialized allocated memory will be initialized to 0xa5.
}


int main(int argc,char **argv)
{
	char value[256] = {"123"};

	get_jemalloc_opt_junk(value);
	printf("value = %s\n", value);


	unsigned char *str = je_malloc(1);
	printf("%x\n", *str);
	//If set to “alloc”, each byte of uninitialized allocated memory will be initialized to 0xa5.
}




