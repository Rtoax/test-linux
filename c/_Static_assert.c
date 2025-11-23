#include <math.h>
#include <stdio.h>

int main(void)
{
	_Static_assert(1, "ERROR");
#ifdef ERROR
	_Static_assert(0, "ERROR");
#endif
	return 0;
}
