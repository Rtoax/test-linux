// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2024-2025 Rong Tao */
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "syscall_helpers.h"


int create_file(const char *filename, char ch, size_t bytes)
{
	int i;
	FILE *fp;

	fp = fopen(filename, "w");
	for (i = 0; i < bytes; i++)
		fwrite(&ch, sizeof(char), 1, fp);
	fclose(fp);

	return 0;
}

off_t file_seek_end(const char *filename)
{
	int fd;
	off_t off;

	fd = open(filename, O_RDONLY);
	off = lseek(fd, 0, SEEK_END);

	close(fd);
	return off;
}
