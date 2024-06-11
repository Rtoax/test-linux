#include <stdio.h>
#include <stdarg.h>

void fun(const char *fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	vprintf(fmt, arg);
	va_end(arg);
}

int main(void)
{
	fun("Rong Tao love %s\n", "Xue Yuehua");
	return 0;
}
