// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2024-2026 Rong Tao. All rights reserved. */
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/types.h>
#include <sys/syscall.h>
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

int sys_reboot(int magic, int magic2, int op, void *arg)
{
	int err = syscall(__NR_reboot, magic, magic2, op, arg);
	if (err)
		errno = -err;
	return err;
}
