#include <stdio.h>

#define offsetof(type, member) __builtin_offsetof(type, member)

struct A{
	int a;
	int b;
};

int main(void)
{
	printf("%ld\n", offsetof(struct A, b));
	return 0;
}
