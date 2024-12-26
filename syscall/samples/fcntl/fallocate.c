#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>

#define TEST_FILE	"falloc.dat"
#define TEST_FILE_LSEEK	"falloc.lseek.dat"

#ifdef POSIX
#define fallocate posix_fallocate
#endif

int openfile(char *file)
{
	unlink(file);
	return open(file, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
}

int main(int argc, char *argv[])
{
	int i, fd;
	int offset = 4096;
	int len = 4096 * 3;
	char *buf;

	buf = malloc(len + offset);
	for (i = 0; i < len + offset; i++)
		buf[i] = 'a';

	fd = openfile(TEST_FILE);
	write(fd, buf, len + offset);
	/**
	 * Tracing: sudo bpftrace -e 'kprobe:*_fallocate { @[probe] = count() }'
	 *
	 * This is a nonportable, Linux-specific system call. For the portable,
	 * POSIX.1-specified method of ensuring that space is allocated for a
	 * file, see posix_fallocate(3). See fallocate(2).
	 */
#ifdef POSIX
	posix_fallocate(fd, offset, len);
#else
	int fallocmode = FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE;
	int ret = fallocate(fd, fallocmode, offset, len);
	if (ret == -1) {
		perror("fallocate");
		exit(1);
	}
#endif
	close(fd);

	/* Test lseek */
	fd = openfile(TEST_FILE_LSEEK);
	lseek(fd, offset, SEEK_SET);
	write(fd, buf, len);
	close(fd);

	free(buf);
	return 0;
}
