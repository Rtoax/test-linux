/**
 * https://gcc.gcc.gnu.narkive.com/WvwssETm/builtin-apply-args-gcc-4-1-1
 * gcc-src/gcc/testsuite/gcc.dg/builtin-apply2.c
 */
#include <stdio.h>
#include <stdarg.h>

#define INTEGER_ARG 5

void foo(char *name, int d, int e, int f, int g)
{
	printf("name = %s, 13 = %d, 72 = %d, 89 = %d, 5 = %d\n",
		name, d, e, f, g);
}

void bar(char *name, ...)
{
	void **arg;
	arg = __builtin_apply_args();
	__builtin_apply(foo, arg, 24);
}

int main(void)
{
	bar("eeee", 13, 72, 89, INTEGER_ARG);
	return 0;
}