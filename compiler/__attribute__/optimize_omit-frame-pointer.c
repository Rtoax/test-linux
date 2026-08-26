#include "optimize.h"

_omit_frame_pointer int foo(void)
{
	int i = 0;
	return i + 1;
}

int main(void)
{
	foo();
	return 0;
}
