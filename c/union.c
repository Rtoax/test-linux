#include <stdio.h>

struct foo {};
#if ERROR
/* error: ‘foo’ defined as wrong kind of tag */
union foo {};
#endif
union bar {};

union u1 {
	struct {
		int a;
		char c;
		int b;
	} s0 __attribute__((packed));
	struct {
		int a;
		int b;
	} s1 __attribute__((packed));
} __attribute__((packed)) /* seems like this packed is not work */;

int main(void)
{
	printf("size of u1 %ld\n", sizeof(union u1));
	return 0;
}
