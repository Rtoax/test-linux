#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MQUEUE_NAME "/_rtoax_mq_"

mqd_t mqd;
int max_prio;

void *task1_fn(void *arg)
{
	char msg[64] = "abc";
	struct timespec timeout = {2, 0};
	timeout.tv_sec = time(NULL) + 2;
	mq_timedsend(mqd, (char *)msg, strlen(msg) + 1, max_prio, &timeout);
	printf("send %s\n", msg);
	return NULL;
}

void *task2_fn(void *arg)
{
	char buffer[256];
	mq_receive(mqd, buffer, sizeof(buffer), 0);
	printf("recv %s\n", buffer);
	return NULL;
}

int main(void)
{
	struct mq_attr attr;
	pthread_t task1, task2;

	max_prio = sysconf(_SC_MQ_PRIO_MAX) - 1;

	mq_unlink(MQUEUE_NAME);

	attr.mq_flags = 0;
	attr.mq_msgsize = 1024;
	attr.mq_maxmsg = 256;

	mqd = mq_open(MQUEUE_NAME, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO, &attr);

	pthread_create(&task1, NULL, task1_fn, NULL);
	pthread_create(&task2, NULL, task2_fn, NULL);

	pthread_join(task1, NULL);
	pthread_join(task2, NULL);

	mq_close(mqd);
	mq_unlink(MQUEUE_NAME);
	return 0;
}
