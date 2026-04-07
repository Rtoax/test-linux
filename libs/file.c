// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int secure_temp_file(char filename[128])
{
	static int random_fd = -1;
	unsigned int random;
	int fd;
	struct stat stat_buf;
	if (random_fd == -1) {
		random_fd = open("/dev/random", O_RDONLY);
		if (random_fd == -1)
			return -1;
	}
	if (read(random_fd, &random, sizeof(random)) != sizeof(random))
		return -1;

	sprintf(filename, "/tmp/%u", random);
	printf("filename: %s\n", filename);

	fd = open(filename, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return -1;
	if (lstat(filename, &stat_buf) == -1)
		return -1;
	if (!S_ISREG(stat_buf.st_mode))
		return -1;
	if (stat_buf.st_uid != geteuid() || stat_buf.st_gid != getegid())
		return -1;
	if ((stat_buf.st_mode & ~(S_IRUSR | S_IWUSR)) != 0)
		return -1;
	return fd;
}

#if defined(TEST_MAIN)
int main(void)
{
	char filename[128];
	int fd = secure_temp_file(filename);

	close(fd);
	unlink(filename);
	return 0;
}
#endif
