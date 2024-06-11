#include <stdarg.h>
#include <stdio.h>

int fun(const char *fmt, ...)
{
	int n;
	va_list ap, save;
	va_start(ap, fmt);
	va_copy(save, ap);
	n = vfprintf(stdout, fmt, save);
	va_end(ap);
	return n;
}

int main(void)
{
	fun("Rong %s\n", "Tao");
	return 0;
}
