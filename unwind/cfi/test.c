/**
 *
 *	libunwind详解: https://blog.csdn.net/Rong_Toa/article/details/110846509
 *
 *  显示 .eh_frame 信息
 *	readelf -wF a.out
 *
 *	显示 .eh_frame 原始信息
 *	readelf -wf a.out
 */
#include <stdio.h>

int test(int x)
{
	int c =10;
	return x*c;
}

void main()
{
	int a,b;
	a = 10;
	b = 11;
	a = test(a+b);
}
