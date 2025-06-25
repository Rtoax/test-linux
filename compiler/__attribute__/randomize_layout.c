#include <stdio.h>

#if 0 /* TODO */
#define __randomize_layout __attribute__((randomize_layout))
#else
#define __randomize_layout
#endif

struct __randomize_layout rt_struct {
	int a;
	char b;
	long c;
	short d;
};

int main(void)
{
	struct rt_struct rt;

	printf("size of rt_struct is %ld\n", sizeof(struct rt_struct));
	printf("address of struct is %p\n", &rt);
	printf("address of a is %p\n", &rt.a);
	printf("address of b is %p\n", &rt.b);
	printf("address of c is %p\n", &rt.c);
	printf("address of d is %p\n", &rt.d);
	return 0;
}
