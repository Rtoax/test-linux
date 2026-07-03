// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * use to
 * - plotcake::utils.c
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

int open_secure_temp_file(char filename[128])
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
	fprintf(stderr, "temp file name: %s\n", filename);

	fd = open(filename, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		fprintf(stderr, "open(%s) = %m\n", filename);
		return -errno;
	}
	if (lstat(filename, &stat_buf) == -1)
		return -1;
	if (!S_ISREG(stat_buf.st_mode))
		return -1;
	if (stat_buf.st_uid != geteuid() || stat_buf.st_gid != getegid()) {
		fprintf(stderr, "%s uid %d wrong\n", filename, stat_buf.st_uid);
		return -1;
	}
	if ((stat_buf.st_mode & (S_IRUSR | S_IWUSR)) != (S_IRUSR | S_IWUSR)) {
		fprintf(stderr, "%s mode %d wrong\n", filename,
			stat_buf.st_mode);
		return -1;
	}
	return fd;
}

#if defined(TEST_MAIN)
int main(void)
{
	int err;
	char filename[128];
	int fd = open_secure_temp_file(filename);
	char *buf;

	err = write(fd, "Hello", 6);
	printf("write(%d, ...) = %d\n", fd, err);

	close(fd);

	alloc_buf_read_file(filename, &buf);

	printf("buf: %s\n", buf);
	if (strcmp(buf, "Hello")) {
		fprintf(stderr, "alloc_buf_read_file test failed.\n");
		exit(1);
	}

	free(buf);

	unlink(filename);
	return 0;
}
#endif
