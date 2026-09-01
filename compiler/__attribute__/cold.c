#include <stdio.h>
#include "cold.h"

__cold int foo(void)
{
	return 0;
}

__hot int bar(void)
{
	return 0;
}

int fun(void)
{
	return 0;
}

int main(void)
{
	return 0;
}
