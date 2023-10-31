#include "unused.h"

#ifdef __clang__
void func1(int a, int b, int c)
#else
void func1(a, b, c)
int a, b, c;
#endif
{}

#ifdef __clang__
void func2(int a, int b, int c, int d, int e, int f)
#else
void func2(a, b, c, d, e, f)
int a, b, c, d, e, f;
#endif
{}

#ifdef __clang__
void func3(int a, int b, int c, int d, int e, int f, int g, int h)
#else
void func3(a, b, c, d, e, f, g, h)
int a, b, c, d, e, f, g, h;
#endif
{
	int __unused i = a + b + c + d + e + f + g + h;
}

void func0(){}

int main(void)
{
#if 1
	int a, b, c, d, e, f, g, h;
	a = 1;
	b = 2;
	c = 3;
	d = 4;
	e = 5;
	f = 6;
	g = 7;
	h = 8;

	func1(a,b,c);
	func2(a,b,c,d,e,f);
	func3(a,b,c,d,e,f,g,h);
#endif
}
