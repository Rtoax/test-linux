#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>


int __attribute__((format(printf, 2, 3)))
log_error(const char *err, const char *fmt, ...)
{
	int ret;
	va_list arg;
	va_start(arg, fmt);
	printf("[%s] ", err);
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
	log_error("This is an error type", "%d, %d, %d\n", 1, 3, 4);
	return 0;
}
