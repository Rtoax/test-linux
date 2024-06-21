#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdlib.h>
#include <string.h>
#include <libaio.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define NR_EVENT	10
#define BUF_LEN	1024

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

int main(void)
{
	int i;
	int ret;
	int ifd, ofd;
	char *wbuf;
	io_context_t context;
	struct iocb io[2];
	struct timespec timeout;
	struct iocb *iocbs[ARRAY_SIZE(io)] = {
		&io[0],
		&io[1],
	};
#define IO_READER	0
#define IO_WRITER	1

	posix_memalign((void **)&wbuf, 512, BUF_LEN);

	memset(wbuf, '@', BUF_LEN);
	memset(&context, 0, sizeof(io_context_t));
	timeout.tv_sec = 0;
	timeout.tv_nsec = 10000000;

	ifd = open("/etc/os-release", O_RDONLY);
	if (ifd < 0) {
		perror("open");
		exit(1);
	}

	ofd = open("test3.dat", O_CREAT | O_RDWR | O_DIRECT, 0644);
	if (ofd < 0) {
		printf("open error: %d\n", errno);
		return 0;
	}

	ret = io_setup(NR_EVENT, &context);
	if (ret != 0) {
		printf("io_setup error: %d\n", errno);
		return 0;
	}

	/* reader and writer use same buffer */
	io_prep_pread(&io[IO_READER], ifd, wbuf, BUF_LEN, 0);
	io_prep_pwrite(&io[IO_WRITER], ofd, wbuf, BUF_LEN, 0);

	ret = io_submit(context, ARRAY_SIZE(iocbs), iocbs);
	if (ret != 2) {
		printf("io_submit error: %d\n", ret);
		io_destroy(context);
		return -1;
	}

	/* read and write */
	for (i = 0; i < ARRAY_SIZE(iocbs); i++) {
		struct io_event e[1];
		ret = io_getevents(context, 1, 1, e, &timeout);
		if (ret <= 0) {
			printf("io_getevents error: %d\n", ret);
			continue;
		}
		struct iocb *cb = (struct iocb *)e->obj;
		fprintf(stderr, "%p %p %p\n", &io[0], &io[1], cb);
		if (cb == &io[IO_READER]) {
			printf("Read event, ");
		} else if (cb == &io[IO_WRITER]) {
			printf("Write event, ");
		}
		printf("result, res2: %ld, res: %ld\n", e[0].res2, e[0].res);
	}

	free(wbuf);
	io_destroy(context);

	return 0;
}
