#include <stdio.h>

/**
 * https://gcc.gnu.org/onlinedocs/gcc/Constructing-Calls.html
 */
int myprintf(FILE *f, const char *format, ...)
{
	int r = fprintf(f, "myprintf: ");
	if (r < 0)
		return r;
	int s = fprintf(f, format, __builtin_va_arg_pack());
	if (s < 0)
		return s;
	return r + s;
}

int main(void)
{
	myprintf(stdout, "hello world: %s\n", "RongTao");
	return 0;
}
