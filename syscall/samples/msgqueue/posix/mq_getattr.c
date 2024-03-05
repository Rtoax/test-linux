#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define	FILE_MODE	(S_IRWXU | S_IRWXG | S_IRWXO)

int main(void)
{
	struct mq_attr attr;
	struct mq_attr attr2;
	char *filename = "/msgq1";

	int flags = O_RDWR | O_CREAT;
	flags |= O_EXCL;

	attr.mq_flags = 0;
	attr.mq_msgsize = 1024;
	attr.mq_maxmsg = 256;

	mqd_t mqd = mq_open(filename, flags, FILE_MODE, &attr);
	if (mqd == -1) {
		fprintf(stderr, "mq_open failed, %s\n", strerror(errno));
		return -errno;
	}

	mq_getattr(mqd, &attr2);

	printf("MAXMSG = %ld, MSGSIZE = %ld, CURRENT MSG = %ld\n",
		attr2.mq_maxmsg, attr2.mq_msgsize, attr2.mq_curmsgs);

	mq_close(mqd);
	mq_unlink(filename);
	return 0;
}

