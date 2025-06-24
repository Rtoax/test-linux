#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>


void test_vasprintf(char *fmt, ...)
{
	char *output = NULL;
	int ret;
	va_list va;

	va_start(va, fmt);

	ret = vasprintf(&output, fmt, va);
	if (ret < 0) {
		perror("vasprintf");
	} else {
		printf("output: %s", output);
		free(output);
	}

	va_end(va);
}

int main(void)
{
	test_vasprintf("Hello, %s\n", "Rong Tao");

	return 0;
}
