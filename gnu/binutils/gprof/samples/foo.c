#include <stdio.h>

struct test {
	void (*f)(void);
};

void caller(struct test *ts, int n)
{
	int i;
	struct test *t;

	for (i = 0; i < n; i++) {
		t = &ts[i];
		t->f();
	}
}

void fb1(void)
{
}
void fb2(void)
{
	fb1();
}
void fb3(void)
{
	fb1();
	fb2();
}
void fb4(void)
{
	fb1();
	fb2();
	fb3();
}
void fb5(void)
{
	fb1();
	fb2();
	fb3();
	fb4();
}
void fb6(void)
{
	fb1();
	fb2();
	fb3();
	fb4();
	fb5();
}

struct test tests_fb[] = {
	{ fb1 }, { fb2 }, { fb3 }, { fb4 }, { fb5 }, { fb6 },
};

void core(void)
{
	caller(tests_fb, sizeof(tests_fb) / sizeof(tests_fb[0]));
}

void f1(void)
{
	core();
}
void f2(void)
{
	core();
	f1();
}
void f3(void)
{
	core();
	f1();
	f2();
}
void f4(void)
{
	core();
	f1();
	f2();
	f3();
}
void f5(void)
{
	core();
	f1();
	f2();
	f3();
	f4();
}
void f6(void)
{
	core();
	f1();
	f2();
	f3();
	f4();
	f5();
}

struct test tests_f[] = {
	{ f1 }, { f2 }, { f3 }, { f4 }, { f5 }, { f6 },
};

int main(void)
{
	caller(tests_f, sizeof(tests_f) / sizeof(tests_f[0]));
	return 0;
}
