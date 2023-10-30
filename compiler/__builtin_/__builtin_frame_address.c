#include <stdio.h>

#define FRAME(i) __builtin_frame_address(i)


int f1(void)
{
	long I = 1;
	printf("f1: %p, %p\n", FRAME(0), &I);
	printf("f1: %p, %p\n", FRAME(1), &I);
	printf("f1: %p, %p\n", FRAME(2), &I);
	printf("f1: %p, %p\n", FRAME(3), &I);
}

int f2(void)
{
	long I = 2;
	printf("f2: %p, %p\n", FRAME(0), &I);
	printf("f2: %p, %p\n", FRAME(1), &I);
	printf("f2: %p, %p\n", FRAME(2), &I);
	return f1();
}

int f3(void)
{
	long I = 3;
	printf("f3: %p, %p\n", FRAME(0), &I);
	printf("f3: %p, %p\n", FRAME(1), &I);
	return f2();
}


typedef int (*fn)(void);

struct test {
	int i;
	long l;
	fn f;
};
struct test t1;

int F(void)
{
	t1.i = 2;
	t1.l = 3;
	t1.f = f1;

	printf("t1: %p\n", &t1);
	printf("F : %p\n", __builtin_frame_address(0));

	t1.f();

	return 1;
}

int main(void)
{
	long I = 4;
	F();
	printf("ma: %p, %p\n", FRAME(0), &I);
	return f3();
}