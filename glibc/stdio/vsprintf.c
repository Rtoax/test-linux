#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>


void test_vsprintf(char *fmt, ...)
{
	int ret;
	char *output = NULL;
	va_list va;

	va_start(va, fmt);

	output = malloc(1024);
	ret = vsprintf(output, fmt, va);
	if (ret < 0) {
		perror("vfprintf");
	} else {
		printf("output = %s", output);
	}

	va_end(va);
}

int main(void)
{
	test_vsprintf("Hello, %s\n", "Rong Tao");

	return 0;
}
