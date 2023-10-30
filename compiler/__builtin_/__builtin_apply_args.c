/**
 * https://gcc.gcc.gnu.narkive.com/WvwssETm/builtin-apply-args-gcc-4-1-1
 * gcc-src/gcc/testsuite/gcc.dg/builtin-apply2.c
 */
#include <stdio.h>
#include <stdarg.h>

#if 0
void * __builtin_apply(void (*function)(), void *arguments, size_t size);
void ** __builtin_apply_args();
void __builtin_return(void *result);
__builtin_va_arg_pack();
size_t __builtin_va_arg_pack_len();
#endif

void foo(char *name, int d, int e, int f, int g)
{
	printf("name = %s, 13 = %d, 72 = %d, 89 = %d, 5 = %d\n",
		name, d, e, f, g);
}

void foo2(char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	vprintf(fmt, va);
	va_end(va);
}

void bar(char *name, ...)
{
	void **arg;
	void *rslt;

	arg = __builtin_apply_args();

	rslt = __builtin_apply(foo, arg, 24);
	rslt = __builtin_apply(foo, arg, 24);

	/**
	 * TODO: expected ‘void (*)()’ but argument is of type ‘void (*)(char *, ...)
	 */
	rslt = __builtin_apply(foo2, arg, 24);

	__builtin_return(rslt);
}

int main(void)
{
	bar("eeee", "%d %d %d %d\n", 13, 72, 89, 5);
	return 0;
}
