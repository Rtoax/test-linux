#include "lib.h"

int lf1(int i)
{
	return 1 + i;
}

int lf2(int i)
{
	return 2 + i + lf1(i);
}
