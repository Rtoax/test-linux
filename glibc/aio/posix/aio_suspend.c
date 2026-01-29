#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <aio.h>

#define BUFFER_SIZE 1024
#define MAX_LIST 2

int main(int argc, char **argv)
{
	struct aiocb rd;
	int fd, ret, counter;
	struct aiocb const *aiocb_list[MAX_LIST];
	void *buf;

	fd = open("/etc/os-release", O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	bzero(&rd, sizeof(rd));

	buf = malloc(BUFFER_SIZE + 1);

	rd.aio_buf = buf;
	rd.aio_fildes = fd;
	rd.aio_nbytes = BUFFER_SIZE;
	rd.aio_offset = 0;

	aiocb_list[0] = &rd;

	ret = aio_read(&rd);
	if (ret < 0) {
		perror("aio_read");
		exit(1);
	}

	counter = 0;

	while (aio_error(&rd) == EINPROGRESS) {
		printf("%s", (char *)rd.aio_buf);
		++counter;
	}

	printf("Waiting aio finish...\n");

	ret = aio_suspend(aiocb_list, MAX_LIST, NULL);

	ret = aio_return(&rd);
	printf("\nReturn: %d\n", ret);

	free(buf);
	return 0;
}
