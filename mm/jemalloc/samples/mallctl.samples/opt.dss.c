#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//opt.dss (const char *) r-
//	dss (sbrk(2)) allocation precedence(优先权) as related to mmap(2) allocation.
//  The following settings are supported if sbrk(2)
//	is supported by the operating system: “disabled”, “primary”, and “secondary”; otherwise only
//	“disabled” is supported. The default is “secondary” if sbrk(2) is supported by the operating system;
//	“disabled” otherwise.


void get_jemalloc_opt_dss(char *value) {
	size_t size = 32;
	je_mallctl("opt.dss", value, &size, NULL, 0);
}


int main(int argc,char **argv)
{
	char value[256] = {"123"};

	get_jemalloc_opt_dss(value);
	printf("value = %s\n", value);
}

