#include <math.h>
#include <stdio.h>

_Static_assert(1, "ERROR");
#ifdef ERROR
_Static_assert(0, "ERROR");
#endif

int main(void)
{
	return 0;
}
