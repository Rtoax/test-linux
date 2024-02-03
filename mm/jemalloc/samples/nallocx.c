#include <stdio.h>
#include <jemalloc/jemalloc.h>

int main(void)
{
	size_t s1 = nallocx(1024, MALLOCX_LG_ALIGN(8));
	printf("size = %ld.\n", s1);
}

