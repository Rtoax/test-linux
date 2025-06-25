#include <stdio.h>

typedef int v4si __attribute__((vector_size(16)));

/*
v4si f (v4si a, v4si b, v4si c)
{
	v4si tmp = __builtin_addv4si(a, b);
	return (v4si)__builtin_mulv4si(tmp, c);
}
*/

int main(void)
{
	v4si a;
	v4si *pa;

#define PRINT_SIZE(v) printf("%-8s %ld\n", #v, sizeof(v));

	PRINT_SIZE(v4si);
	PRINT_SIZE(v4si*);
	PRINT_SIZE(a);
	PRINT_SIZE(&a);
	PRINT_SIZE(pa);
	PRINT_SIZE(*pa);

	return 0;
}
