/**
 * 显示 .eh_frame 信息
 * readelf -wF a.out
 *
 * 显示 .eh_frame 原始信息
 * readelf -wf a.out
 */
#include <stdio.h>

int test(int x)
{
	int c = 10;

	return x * c;
}

int main(void)
{
	int a, b;

	a = 10;
	b = 11;

	printf("hello test~, %d\n", a + b);

	a = test(a + b);

	return 0;
}
