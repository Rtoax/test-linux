#include <stdio.h>
#include <gperftools/tcmalloc.h>
#include <gperftools/nallocx.h>

int main(void)
{
	size_t size = tc_nallocx(1024, MALLOCX_LG_ALIGN(1024));
	printf("%ld\n", size);
}


