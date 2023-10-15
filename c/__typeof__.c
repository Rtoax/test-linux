#include <stdlib.h>
#include "unused.h"

struct test {
	int i;
};

int main(void)
{
	struct test t1;
	__typeof__(t1) __unused t2;

	t2.i = 1;

	return 0;
}
