#include "optimize.h"

_OPTIMIZE_O0 int foo(void)
{
	int i = 0;
	return i + 1;
}

int main(void)
{
	return foo();
}
