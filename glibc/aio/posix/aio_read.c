#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <aio.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
	struct aiocb rd;
	const char *filename = "/etc/os-release";
	int fd, ret, counter, times;
	struct stat stat;
	void *buf;

	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	fstat(fd, &stat);

	bzero(&rd, sizeof(rd));

	buf = malloc(BUFFER_SIZE + 1);

	rd.aio_buf = buf;
	rd.aio_fildes = fd;
	rd.aio_nbytes = BUFFER_SIZE;
	rd.aio_offset = 0;

	ret = aio_read(&rd);
	if (ret < 0) {
		perror("aio_read");
		exit(1);
	}

	counter = 0;
	times = 0;
	while (aio_error(&rd) == EINPROGRESS) {
		/* Print text and count number of bytes */
		counter += printf("%s", (char *)rd.aio_buf);
		times++;
	}

	ret = aio_return(&rd);
	printf("\nReturn: %d, counter %d, stat size %ld (times %d)\n", ret,
	       counter, stat.st_size, times);

	free(buf);

	return 0;
}
