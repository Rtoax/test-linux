#include <math.h>
#include <stdio.h>

#define STATIC_ASSERT(expr, msg) \
	typedef char static_assert_failed_##msg[(expr) ? 1 : -1]

_Static_assert(1, "ERROR");
static_assert(1, "ERROR");
STATIC_ASSERT(1, ERROR);
#ifdef ERROR
_Static_assert(0, "ERROR");
static_assert(0, "ERROR");
STATIC_ASSERT(0, ERROR);
#endif

int main(void)
{
	return 0;
}
