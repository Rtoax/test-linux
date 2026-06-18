/**
 * __VA_ARGS__
 *
 * Refs:
 * - https://en.wikipedia.org/wiki/Variadic_macro
 */

#include <stdio.h>

#define print1(fmt, ...) printf(fmt, __VA_ARGS__)
#define print2(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define print3(fmt...) printf(fmt)

/* GNU extend */
#define FUNC_CALL(func, ...) func(__VA_ARGS__)

void test_print(int a, int b)
{
	printf("hello, %s %s\n", "rong", "tao");
	print1("hello, %s %s\n", "rong", "tao");
	print2("hello, %s %s\n", "rong", "tao");
	print2("hello, rong tao\n");
	print3("hello, %s %s\n", "rong", "tao");
	print3("hello, rong tao\n");
}

int main(void)
{
	FUNC_CALL(test_print, 1, 2);

	FUNC_CALL(printf, "hello\n");
	FUNC_CALL(printf, "hello %s\n", "rongtao");

	return 0;
}
