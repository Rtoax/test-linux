// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

unsigned long usecs(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000UL + tv.tv_usec;
}

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

/**
 * see test-linux libs/file.c
 */
/**
 * @buf: need free()
 * @return: -errno if failed, file size if success
 */
long alloc_buf_read_file(const char *filename, char **buf)
{
	FILE *fp = fopen(filename, "rb");
	if (!fp) {
		fprintf(stderr, "open %s failed, %m\n", filename);
		return -errno;
	}

	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	*buf = (char *)malloc(size + 1);
	if (!buf) {
		fprintf(stderr, "alloc memory failed, %m.\n");
		fclose(fp);
		return -errno;
	}

	fread(*buf, 1, size, fp);
	(*buf)[size] = '\0';
	fclose(fp);

	return size;
}
