#include <stdio.h>

struct alignas(16) test1 {
	char c;
	unsigned long l;
};

int main(void)
{
	printf("Sizeof(test1) = %ld\n", sizeof(struct test1));
	return 0;
}
