#include <stdio.h>

#define print1(fmt, ...) printf(fmt, __VA_ARGS__)
#define print2(fmt, ...) printf(fmt, ##__VA_ARGS__)

int main(void)
{
	printf("hello, %s %s\n", "rong", "tao");
	print2("hello, %s %s\n", "rong", "tao");
}
