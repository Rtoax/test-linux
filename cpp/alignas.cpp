#include <stdio.h>
#include <stdalign.h>
#include <inttypes.h>

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
#if defined(M32)
# define PRI	PRId32
#else
# define PRI	PRId64
#endif
	alignas(64) int buffer[10];
	printf("Sizeof(buffer) = %" PRI "\n", sizeof(buffer));
	printf("Sizeof(test1) = %" PRI "\n", sizeof(struct test1));
	return 0;
}
