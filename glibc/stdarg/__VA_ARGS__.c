#include <stdio.h>

#define print1(fmt, ...) printf(fmt, __VA_ARGS__)
#define print2(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define print3(fmt...) printf(fmt)

int main(void)
{
	printf("hello, %s %s\n", "rong", "tao");
	print1("hello, %s %s\n", "rong", "tao");
	print2("hello, %s %s\n", "rong", "tao");
	print2("hello, rong tao\n");
	print3("hello, %s %s\n", "rong", "tao");
	print3("hello, rong tao\n");
	return 0;
}
