#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//opt.thp (const char *) r-
//	Transparent hugepage (THP) mode. Settings "always", "never" and "default" are available if THP is supported by the
//	operating system. The "always" setting enables transparent hugepage for all user memory mappings with MADV_HUGEPAGE; "
//	never" ensures no transparent hugepage with MADV_NOHUGEPAGE; the default setting "default" makes no changes. Note that
//	: this option does not affect THP for jemalloc internal metadata (see opt.metadata_thp); in addition, for arenas with
//	customized extent_hooks, this option is bypassed as it is implemented as part of the default extent hooks.


void get_jemalloc_opt_thp(char *value) {
	size_t size = 32;
	je_mallctl("opt.thp", value, &size, NULL, 0);
	//If set to “alloc”, each byte of uninitialized allocated memory will be initialized to 0xa5.
}


int main(int argc,char **argv)
{
	char value[256] = {"123"};

	get_jemalloc_opt_thp(value);
	printf("value = %s\n", value);


	unsigned char *str = je_malloc(1);
	printf("%x\n", *str);
	//If set to “alloc”, each byte of uninitialized allocated memory will be initialized to 0xa5.
}





