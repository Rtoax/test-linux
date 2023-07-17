#include <stdio.h>

#include "align.h"

struct a {
	int a;
};

struct b {
	int a;
} __aligned(64);

struct c {
	char a;
	long b;
	int c;
};

struct d {
	char a;
	long b;
	int c;
} __aligned(1);

struct e {
	char a;
	long b;
	int c;
} __packed;


int main(void)
{
	printf("size of a = %ld\n", sizeof(struct a));
	printf("size of b = %ld\n", sizeof(struct b));
	printf("size of c = %ld\n", sizeof(struct c));
	printf("size of d = %ld\n", sizeof(struct d));
	printf("size of e = %ld\n", sizeof(struct e));

	return 0;
}
