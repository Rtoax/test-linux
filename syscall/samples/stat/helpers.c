#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#include "helpers.h"


void print_stat(const char *file, struct stat *stat)
{
	unsigned int maj, min;

	printf("----- %s -----\n", file);
	printf("mode: %x\n", stat->st_mode);
	printf("ino: %ld\n", stat->st_ino);
	printf("size: %ld\n", stat->st_size);
	printf("block: size: %ld, count %ld\n", stat->st_blksize,
		stat->st_blocks);

	if (stat->st_mode & S_IWUSR)
		printf("Owning user can write.\n");

	printf("type:S_ISDIR:%d\n", S_ISDIR(stat->st_mode));
	printf("type:S_ISCHR:%d\n", S_ISCHR(stat->st_mode));
	printf("type:S_ISBLK:%d\n", S_ISBLK(stat->st_mode));
	printf("type:S_ISREG:%d\n", S_ISREG(stat->st_mode));
	printf("type:S_ISLNK:%d\n", S_ISLNK(stat->st_mode));
	printf("type:S_ISSOCK:%d\n", S_ISSOCK(stat->st_mode));
	printf("type:S_IFMT:%d\n", S_IFMT);

	printf("type:S_TYPEISMQ:%d\n", S_TYPEISMQ(stat));
	printf("type:S_TYPEISSEM:%d\n", S_TYPEISSEM(stat));
	printf("type:S_TYPEISSHM:%d\n", S_TYPEISSHM(stat));

	maj = major(stat->st_dev);
	min = minor(stat->st_dev);
	printf("major:%d, minor:%d\n", maj, min);
}

int sys_fstat(int fd, struct stat *statbuf)
{
	return syscall(__NR_fstat, fd, statbuf);
}

int sys_lstat(const char *pathname, struct stat *statbuf)
{
	return syscall(__NR_lstat, pathname, statbuf);
}

int sys_ustat(dev_t dev, struct tl_ustat *ubuf)
{
	return syscall(__NR_ustat, dev, ubuf);
}

void print_ustat(struct tl_ustat *us)
{
	printf("f_tfree: %d\n", us->f_tfree);
	printf("f_tinode: %ld\n", us->f_tinode);
	printf("f_fname: %s\n", us->f_fname);
	printf("f_fpack: %s\n", us->f_fpack);
}
