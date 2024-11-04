#include <stdio.h>

struct test {
	int val;
};

static struct test global_test = { .val = 0xee, };

static struct test *get_test(void)
{
	static struct test *t;
	if (!t)
		t = &global_test;
	return t;
}

int test_test(struct test *pt)
{
	printf("val = %d\n", pt->val);
	return 0;
}

int test(void)
{
	test_test(get_test());
	return 0;
}

int bar(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
	return 0xff;
}

int foo(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
	return bar(a1, a2, a3, a4, a5, a6, a7, a8);
}

int main(void)
{
	int ret;

	ret = foo(1, 2, 3, 4, 5, 6, 7, 8);

	test();

	(void)ret;

	return 0;
}
