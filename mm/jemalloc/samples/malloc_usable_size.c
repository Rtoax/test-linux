#include <stdio.h>
#include <string.h>
#include <jemalloc/jemalloc.h>

int main(void)
{
	int *I = mallocx(1024, MALLOCX_LG_ALIGN(8));

	size_t s1;

	s1 = malloc_usable_size(I);
	printf("size = %ld.\n", s1);

	memset(I, 'A', 256);
	printf("%s\n", (char*)I);

	s1 = malloc_usable_size(I+256);
	printf("size = %ld.\n", s1);

	free(I);
}
