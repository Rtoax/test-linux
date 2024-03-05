#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

struct dbg_msg {
	unsigned long msg_seq;
	unsigned long msg_ack;
};

#define MQUEUE_NAME "/_rtoax_mq_"

mqd_t mqd;

void *task1_fn(void *arg)
{
	int ret;
	struct dbg_msg dmsg;

	dmsg.msg_seq = 11;
	dmsg.msg_ack = 0;


	while (1) {
		ret = mq_send(mqd, (char*)&dmsg, sizeof(struct dbg_msg), 0);
		if (ret == -1) {
			continue;
		}
		printf("T1: send seq(%ld), ack(%ld)\n", dmsg.msg_seq, dmsg.msg_ack);

		char buffer[1024];
		struct timespec timeout = {2, 0};
		timeout.tv_sec = time(NULL) + 2;
		ret = mq_timedreceive(mqd, buffer, 1024, 0, &timeout);
		if (ret > 0) {
			struct dbg_msg *pdmsg = (struct dbg_msg *)buffer;
			printf("T1: recv seq(%ld), ack(%ld)\n", pdmsg->msg_seq, pdmsg->msg_ack);
			dmsg.msg_seq = pdmsg->msg_seq;
			dmsg.msg_ack = pdmsg->msg_ack;
		}

		sleep(1);
	}
}

void *task2_fn(void *arg)
{
	int ret;
	char buffer[1024];

	struct dbg_msg *pdmsg = (void *)buffer;

	while (1) {
		ret = mq_receive(mqd, buffer, 1024, 0);
		if (ret == -1) {
			continue;
		}
		pdmsg = (struct dbg_msg*)buffer;
		printf("T2: recv seq(%ld), ack(%ld)\n", pdmsg->msg_seq, pdmsg->msg_ack);

		pdmsg->msg_seq++;
		pdmsg->msg_ack++;

		ret = mq_send(mqd, (char*)pdmsg, sizeof(struct dbg_msg), 0);
		printf("T2: send seq(%ld), ack(%ld)\n", pdmsg->msg_seq, pdmsg->msg_ack);
	}
}

int main(void)
{
	struct mq_attr attr;
	pthread_t task1, task2;

	mq_unlink(MQUEUE_NAME);
	perror("mq_unlink: ");

	attr.mq_flags = 0;
	attr.mq_msgsize = 1024;
	attr.mq_maxmsg = 256;

	mqd = mq_open(MQUEUE_NAME, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO, &attr);
	if (mqd == -1) {
		fprintf(stderr, "mq_open failed, %s\n", strerror(errno));
		return -errno;
	}

	pthread_create(&task1, NULL, task1_fn, NULL);
	pthread_create(&task2, NULL, task2_fn, NULL);

	pthread_join(task1, NULL);
	pthread_join(task2, NULL);

	return 0;
}
