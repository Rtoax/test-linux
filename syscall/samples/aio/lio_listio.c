#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <aio.h>


#define BUFFER_SIZE 1025
#define MAX_LIST 2

int main(int argc,char **argv)
{
	struct aiocb *listio[MAX_LIST];
	struct aiocb rd, wr;
	int fd_rd, fd_wr, ret;

	fd_rd = open("/etc/os-release", O_RDONLY);
	if (fd_rd < 0) {
		perror("open read");
		exit(1);
	}

	bzero(&rd, sizeof(rd));

	rd.aio_buf = (char *)malloc(BUFFER_SIZE);
	if (rd.aio_buf == NULL) {
		perror("aio_buf");
		exit(1);
	}

	rd.aio_fildes = fd_rd;
	rd.aio_nbytes = 1024;
	rd.aio_offset = 0;
	rd.aio_lio_opcode = LIO_READ;

	listio[0] = &rd;

	fd_wr = open("test2.dat", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd_wr < 0) {
		perror("open write");
		exit(1);
	}

	bzero(&wr, sizeof(wr));

	wr.aio_buf = (char *)malloc(BUFFER_SIZE);
	if (wr.aio_buf == NULL) {
		perror("aio_buf");
		exit(1);
	}

	wr.aio_fildes = fd_wr;
	wr.aio_nbytes = 1024;
	wr.aio_lio_opcode = LIO_WRITE;

	listio[1] = &wr;

	ret = lio_listio(LIO_WAIT, listio, MAX_LIST, NULL);

	ret = aio_return(&rd);
	printf("read: aio_return: %d\n", ret);

	ret = aio_return(&wr);
	printf("write: aio_return: %d\n", ret);

	free((void *)rd.aio_buf);
	free((void *)wr.aio_buf);

	close(fd_rd);
	close(fd_wr);

	return 0;
}
