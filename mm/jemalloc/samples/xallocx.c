#include <stdio.h>
#include <jemalloc/jemalloc.h>


void test_xallocx(void)
{
	size_t s1;
	int *I = mallocx(1024, MALLOCX_LG_ALIGN(8));

	s1 = sallocx(I, 0);
	printf("size = %ld.\n", s1);

	s1 = xallocx(I, 1024, 1024, MALLOCX_LG_ALIGN(8));
	printf("size = %ld.\n", s1);
	s1 = sallocx(I, 0);
	printf("size = %ld.\n", s1);

	s1 = xallocx(I, 2024, 0, MALLOCX_LG_ALIGN(8));
	printf("size = %ld.\n", s1);
	s1 = sallocx(I, 0);
	printf("size = %ld.\n", s1);

	free(I);
}

int main(void)
{
	test_xallocx();
}
