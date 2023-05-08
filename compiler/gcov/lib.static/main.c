#include "lib.h"

int f1(int i)
{
	return 1 + i + lf1(i);
}

int f2(int i)
{
	return 2 + i + lf2(i) + f1(i);
}

int main(void)
{
	int i = 10;

	return f2(i);
}
