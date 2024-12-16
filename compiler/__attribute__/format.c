#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>


int __attribute__((format(printf, 1, 3)))
error(const char *fmt, const char *err, ...)
{
	int ret;
	va_list arg;
	va_start(arg, fmt);
	printf("%s: ", err);
	ret = vprintf(fmt, arg);
	va_end(arg);
	return ret;
}

int rte_log(uint32_t level, uint32_t logtype, const char *format, ...)
#ifdef __GNUC__
#if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 2))
		__attribute__((cold))
#endif
#endif
		__attribute__((format(printf, 3, 4)));

int main(void)
{
	error("%d, %d, %d\n", "Not this kind of type", 1,3,4);
	return 0;
}
