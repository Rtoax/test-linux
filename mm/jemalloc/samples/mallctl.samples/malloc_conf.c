#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//malloc_conf = "xmalloc:true";
//	This option is disabled by default.




int main(int argc,char **argv)
{
	printf("malloc_conf = %s\n", je_malloc_conf);
}




