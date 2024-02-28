#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(void)
{
	char *filename = "/dev/mqueue/msgq1";
	struct mq_attr	attr;
	int flags = O_RDWR | O_CREAT | O_EXCL;

	attr.mq_maxmsg = 100;
	attr.mq_msgsize = 1024;

	mqd_t mqd = mq_open(filename, flags, FILE_MODE, &attr);
	if (mqd == -1) {
		fprintf(stderr, "mq_open failed, %s.\n", strerror(errno));
	}

	mq_close(mqd);
	return 0;
}

