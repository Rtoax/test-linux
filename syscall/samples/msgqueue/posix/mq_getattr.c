#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>

#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(void)
{
	struct mq_attr attr;
	struct mq_attr attr2;
	char *filename = "/dev/mqueue/msgq1";
	printf("filename = %s\n", filename);

	int flags = O_RDWR | O_CREAT;
	flags |= O_EXCL;

	attr.mq_maxmsg = 1024;
	attr.mq_msgsize = 1024;

	mqd_t mqd = mq_open(filename, flags, FILE_MODE, &attr);
	printf("MDQ = %d\n", mqd);

	mq_getattr(mqd, &attr2);
	printf("MAXMSG = %ld, MSGSIZE = %ld, CURRENT MSG = %ld\n",
		attr2.mq_maxmsg, attr2.mq_msgsize, attr2.mq_curmsgs);

	mq_close(mqd);
	mq_unlink(filename);
	return 0;
}

