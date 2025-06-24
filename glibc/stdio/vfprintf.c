#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>


void test_vfprintf(char *fmt, ...)
{
	int ret;
	va_list va;

	va_start(va, fmt);

	ret = vfprintf(stderr, fmt, va);
	if (ret < 0) {
		perror("vfprintf");
	}

	va_end(va);
}

int main(void)
{
	test_vfprintf("Hello, %s\n", "Rong Tao");

	return 0;
}
