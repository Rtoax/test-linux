#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <dirent.h>     /* Defines DT_* constants */
#include <err.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

struct linux_dirent {
	unsigned long  d_ino;
	off_t          d_off;
	unsigned short d_reclen;
	char           d_name[];
};

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
	int fd;
	char d_type;
	char buf[BUF_SIZE];
	long nread;
	struct linux_dirent *d;

	fd = open(argc > 1 ? argv[1] : ".", O_RDONLY | O_DIRECTORY);
	if (fd == -1)
		err(EXIT_FAILURE, "open");

	for (;;) {
#if defined(__aarch64__) || defined(__loongarch64)
		nread = syscall(SYS_getdents64, fd, buf, BUF_SIZE);
#else
		nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
#endif
		if (nread == -1)
			err(EXIT_FAILURE, "getdents");

		if (nread == 0)
			break;

		printf("--------------- nread=%ld ---------------\n", nread);
		printf("inode#    file type  d_reclen  d_off   d_name\n");
		for (size_t bpos = 0; bpos < nread;) {
			d = (struct linux_dirent *) (buf + bpos);
			printf("%8lu  ", d->d_ino);
			d_type = *(buf + bpos + d->d_reclen - 1);
			printf("%-10s ", (d_type == DT_REG) ?  "regular" :
				(d_type == DT_DIR) ?  "directory" :
				(d_type == DT_FIFO) ? "FIFO" :
				(d_type == DT_SOCK) ? "socket" :
				(d_type == DT_LNK) ?  "symlink" :
				(d_type == DT_BLK) ?  "block dev" :
				(d_type == DT_CHR) ?  "char dev" : "???");
			printf("%4d %10jd  %s\n", d->d_reclen,
				(intmax_t) d->d_off, d->d_name);
			bpos += d->d_reclen;
		}
	}

	exit(EXIT_SUCCESS);
}
