#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "compiler.h"

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

__attribute__((format(printf, 3, 4))) __cold int
rte_log(uint32_t level, uint32_t logtype, const char *format, ...);

int main(void)
{
	log_error("This is an error type", "%d, %d, %d\n", 1, 3, 4);
	return 0;
}
