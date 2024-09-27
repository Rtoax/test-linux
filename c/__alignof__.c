#include <stdio.h>
#include <inttypes.h>

#if defined(M32)
# define PRI	PRId32
#else
# define PRI	PRId64
#endif

struct a {
	int a;
	long b;
};

struct b {
	int a;
	long b;
} __attribute__((packed));

int main(void)
{
	printf("%" PRI "\n", __alignof__(struct a));
	printf("%" PRI "\n", __alignof__(struct b));
	return 0;
}
