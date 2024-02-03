#include <stdio.h>
#include <jemalloc/jemalloc.h>

void test_malloc(void)
{
	int i;
	size_t s1;
	int *I = malloc(1024);

	for(i = 0; i < 1024; i++)
		free(I);

	s1 = malloc_usable_size(I);
	printf("size = %ld.\n", s1);
}

void test_mallocx(void)
{
	int i;
	size_t s1;
	int *I = mallocx(1024, MALLOCX_LG_ALIGN(8));

	for(i = 0; i < 1024; i++)
		free(I);

	s1 = malloc_usable_size(I);
	printf("size = %ld.\n", s1);
}

int main(void)
{
	test_malloc();
	test_mallocx();
}
