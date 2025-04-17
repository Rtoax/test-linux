/**
 * Test parameters pass
 */
#if defined(__clang__) || __GNUC__ >= 15
int func1(int a, int b, int c)
#else
int func1(a, b, c)
int a, b, c;
#endif
{
	return a + b + c;
}

#if defined(__clang__) || __GNUC__ >= 15
int func2(int a, int b, int c, int d, int e, int f)
#else
int func2(a, b, c, d, e, f)
int a, b, c, d, e, f;
#endif
{
	return a + b + c + d + e + f;
}

#if defined(__clang__) || __GNUC__ >= 15
int func3(int a, int b, int c, int d, int e, int f, int g, int h)
#else
int func3(a, b, c, d, e, f, g, h)
int a, b, c, d, e, f, g, h;
#endif
{
	return a + b + c + d + e + f + g + h;
}

void func0(void)
{
}

int main(void)
{
	int a, b, c, d, e, f, g, h;

	a = 1;
	b = 2;
	c = 3;
	d = 4;
	e = 5;
	f = 6;
	g = 7;
	h = 8;

	func1(a, b, c);
	func2(a, b, c, d, e, f);
	func3(a, b, c, d, e, f, g, h);
}
