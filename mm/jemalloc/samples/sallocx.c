#include <stdio.h>
#include <jemalloc/jemalloc.h>

int main(void)
{
	int *I = mallocx(1024, MALLOCX_LG_ALIGN(8));

	size_t s1 = sallocx(I, 0);

	printf("size = %ld.\n", s1);

	free(I);
	return 0;
}
