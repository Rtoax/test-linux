/**
 * __VA_OPT__
 *
 * Refs:
 * - https://en.wikipedia.org/wiki/Variadic_macro
 */
#ifdef __cplusplus
#include <iostream>
#endif
#include <stdarg.h>

#define dbgprintf(cformat, ...) \
	realdbgprintf(__FILE__, __LINE__, cformat __VA_OPT__(,) __VA_ARGS__)

int realdbgprintf(const char *file, int line, const char *cfmt, ...)
{
	int n;
	va_list va;
	va_start(va, cfmt);
	n = vprintf(cfmt, va);
	va_end(va);
	return n;
}

int main(void)
{
	dbgprintf("hello\n");
	dbgprintf("hello %s\n", "world");
	return 0;
}
