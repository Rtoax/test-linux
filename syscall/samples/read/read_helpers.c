#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include "read_helpers.h"

int read_off(int fd, off_t off, void *buf, size_t size, bool keepoff)
{
	off_t cur_pos;
	int err, n;

	cur_pos = lseek(fd, 0, SEEK_CUR);

	err = lseek(fd, off, SEEK_SET);
	if (err == (off_t)-1) {
		perror("lseek");
		return -errno;
	}
	n = read(fd, buf, size);

	if (keepoff)
		lseek(fd, cur_pos, SEEK_SET);
	return n;
}
