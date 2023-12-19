#include <stdio.h>
#include <stdalign.h>

#if defined(CPP)
struct alignas(64) test1 {
#else
struct test1 {
#endif
	char c;
	unsigned long l;
};

int main(void)
{
	alignas(64) int buffer[10];
	printf("Sizeof(buffer) = %ld\n", sizeof(buffer));
	printf("Sizeof(test1) = %ld\n", sizeof(struct test1));
	return 0;
}
