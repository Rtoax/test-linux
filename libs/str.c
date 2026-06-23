// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include "str.h"
#include "constants.h"

void *memcpy_c(void *dest, const void *src, size_t n)
{
	char *d = (char *)dest;
	const char *s = (const char *)src;
	while (n--)
		*d++ = *s++;
	return dest;
}

char *strcaseswap(char *str, ssize_t len)
{
	char *c = str;
	while (*c) {
		*c = (*c)&0xdf;
		c++;
	}
	return str;
}

char *vstrjoint(char *dst, const char *fmt, ...) __attribute__((__format__(printf, 2, 3)));
char *vstrjoint(char *dst, const char *fmt, ...)
{
	if (dst == NULL || fmt == NULL)
		return NULL;
	va_list args;
	va_start(args, fmt);
	vsprintf(dst, fmt, args);
	va_end(args);
	return (char*)dst;
}

const char *vstrcat(int nstr, ...)
{
	int i;
	va_list va;
	static char S[1024] = {0};

	memset(S, 0x00, sizeof(S));

	va_start(va, nstr);
	for (i = 0; i < nstr; i++) {
		char *s = va_arg(va, char*);
		strcat(S, s);
	}
	va_end(va);
	return (char *)S;
}

const char *vstrcat_r(char buf[], int nstr, ...)
{
	int i;
	va_list va;

	va_start(va, nstr);
	for (i = 0; i < nstr; i++) {
		char *s = va_arg(va, char *);
		strcat(buf, s);
	}
	va_end(va);
	return (char *)buf;
}

unsigned long str2size(const char *str)
{
	unsigned long size = 0;

	if (!str) {
		errno = -EINVAL;
		return 0;
	}

	if (str[0] == '0' && str[1] == 'x')
		size = strtoull(str, NULL, 16);
	else
		size = strtoull(str, NULL, 10);

	if (strstr(str, "G") || strstr(str, "GB") || strstr(str, "GiB"))
		size *= GiB;
	else if (strstr(str, "M") || strstr(str, "MB") || strstr(str, "MiB"))
		size *= MiB;
	else if (strstr(str, "K") || strstr(str, "KB") || strstr(str, "KiB"))
		size *= KiB;

	return size;
}

/**
 * string to nanoseconds
 *
 * Refs:
 * - tools/ncurses/tools/utils.c
 */
unsigned long str2nsecs(const char *str)
{
	unsigned long ns = 0;
	char *endptr = NULL;

	if (!str) {
		errno = -EINVAL;
		return 0;
	}

	if (str[0] == '0' && str[1] == 'x')
		ns = strtoull(str, &endptr, 16);
	else
		ns = strtoull(str, &endptr, 10);

	if (!endptr || (endptr && *endptr == '\0')) {
		/* do nothing */
	} else if (!strcasecmp(endptr, "s"))
		ns *= 1000000000UL;
	else if (!strcasecmp(endptr, "ms"))
		ns *= 1000000UL;
	else if (!strcasecmp(endptr, "us"))
		ns *= 1000UL;
	else if (!strcasecmp(endptr, "ns"))
		ns *= 1UL;
	else {
		fprintf(stderr, "str2nsecs() is not support string format\n");
		errno = -EINVAL;
		return 0;
	}

	return ns;
}

#ifdef TEST_MAIN
int main(void)
{
	char buf[1024];
	char str[] = {"AbasdADDadLJ"};
	printf("%s->%s\n", str, strcaseswap(str, strlen(str)));

	printf("%ld\n", str2size("1MB"));

#define STR2NSECS(s, v)                                                       \
	do {                                                                  \
		unsigned long __v = str2nsecs(s);                             \
		if (__v != v) {                                               \
			fprintf(stderr,                                       \
				"ERROR: str2nsecs(\"%s\") = %ld != %ld\n", s, \
				__v, v);                                      \
			abort();                                              \
		}                                                             \
	} while (0)
	STR2NSECS("1", 1UL);
	STR2NSECS("111", 111UL);
	STR2NSECS("999", 999UL);
	STR2NSECS("1S", 1000000000UL);
	STR2NSECS("1s", 1000000000UL);
	STR2NSECS("1MS", 1000000UL);
	STR2NSECS("1ms", 1000000UL);

	char cmd[256];
	memset(cmd, 0, 256);
	vstrjoint(cmd, "rongtao: %d", 123);
	printf("cmd: %s\n", cmd);

	printf("%s\n", vstrcat(3, "rongtao", "is", "me"));
	printf("%s\n", vstrcat_r(buf, 3, "rongtao", "is", "me"));

	return 0;
}
#endif
