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
#define BUF_LEN 1024

int main(void)
{
	io_context_t context;
	struct iocb io[1], *p[1] = {&io[0]};
	struct io_event e[1];
	struct timespec timeout;
	char *wbuf;
	int ret;
	int fd;


	posix_memalign((void **)&wbuf, 512, BUF_LEN);

	memset(wbuf, '@', BUF_LEN);
	memset(&context, 0, sizeof(io_context_t));
	timeout.tv_sec = 0;
	timeout.tv_nsec = 10000000;

	fd = open("test3.dat", O_CREAT | O_RDWR | O_DIRECT, 0644);
	if (fd < 0) {
		printf("open error: %d\n", errno);
		return 0;
	}

	if (0 != io_setup(NR_EVENT, &context)) {
		printf("io_setup error: %d\n", errno);
		return 0;
	}

	io_prep_pwrite(&io[0], fd, wbuf, BUF_LEN, 0);

	if ((ret = io_submit(context, 1, p)) != 1) {
		printf("io_submit error: %d\n", ret);
		io_destroy(context);
		return -1;
	}

	while (1) {
		ret = io_getevents(context, 1, 1, e, &timeout);
		if (ret < 0) {
			printf("io_getevents error: %d\n", ret);
			break;
		}
		if (ret > 0) {
			printf("result, res2: %ld, res: %ld\n", e[0].res2, e[0].res);
			break;
		}
	}
	return 0;
}
