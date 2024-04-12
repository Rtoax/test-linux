#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void error(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vprintf(fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}

int main(void)
{
	error("RongTao:%d\n", 123);
	return 0;
}
