#include <stdio.h>
#include <limits.h>

int main(void)
{
	unsigned long addr = ULONG_MAX;

	addr = 0;

	/* show nothing */
	if (addr == ULONG_MAX)
		fprintf(stderr, "addr(%lx) == ULONG_MAX(%lx)\n",
			addr, ULONG_MAX);

	return 0;
}

