#include <stdio.h>

typedef void* (*fptr)(void);

fptr p0 = NULL, p1 = NULL;

void *f1(void)
{
	p0 = __builtin_return_address(0);
	p1 = __builtin_return_address(1);
	return p0;
}

int main(void)
{
	fptr pf = f1();

	(void)pf;
	printf("p0=%p, p1=%p, f1=%p, main=%p\n", p0, p1, f1, main);

	return 0;
}
