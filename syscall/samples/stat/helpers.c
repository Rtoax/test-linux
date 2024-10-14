#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>

#include "helpers.h"


void print_stat(struct stat *stat)
{
	unsigned int maj, min;

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

