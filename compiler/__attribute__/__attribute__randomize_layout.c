#include <stdio.h>

#define __randomize_layout __attribute__((randomize_layout))

struct rt_struct {
	int a;
	char b;
	long c;
	short d;
} __randomize_layout;

int main(void)
{
	printf("sizeof rt_struct = %d\n", sizeof(struct rt_struct));
	return 0;
}