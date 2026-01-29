#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <aio.h>

#define BUFFER_SIZE 1025

static char doc[] = {
	"I like you, as you know!\n" \
	"I dig you, as you know!\n" \
	"I love you, as everyone knows.\n"
};

int main(int argc, char **argv)
{
	struct aiocb wr;
	int ret, fd;
	char *str = doc;

	bzero(&wr, sizeof(wr));

	fd = open("test.dat", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	wr.aio_buf = str;
	wr.aio_fildes = fd;
	wr.aio_nbytes = strlen(str) + 1;

	ret = aio_write(&wr);
	if (ret < 0) {
		perror("aio_write");
		exit(1);
	}

	while (aio_error(&wr) == EINPROGRESS);

	ret = aio_return(&wr);
	printf("Return: %d\n", ret);

	return 0;
}
