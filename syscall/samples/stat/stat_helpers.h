// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once
#include <sys/stat.h>

#ifndef offsetof
#define offsetof(TYPE, MEMBER)    ((size_t)&((TYPE *)0)->MEMBER)
#endif

struct tl_ustat {
	int f_tfree;
	unsigned long f_tinode;
	char f_fname[6];
	char f_fpack[6];
};

void print_stat(const char *file, struct stat *stat);
void print_statx(struct statx *x);
void print_ustat(struct tl_ustat *us);

int sys_fstat(int fd, struct stat *statbuf);
int sys_lstat(const char *pathname, struct stat *statbuf);
int sys_ustat(dev_t dev, struct tl_ustat *ubuf);
