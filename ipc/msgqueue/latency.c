/**
 * Throughput and latency of message queue.
 *
 * 2021-01-04	Rong Tao	Create this
 * 2021-01-05	Rong Tao	Add timestamp, cal latency
 * 2021-01-06	Rong Tao	Add latency
 */
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <sys/msg.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifndef NR_MSG
#define NR_MSG   1000000
#endif

#define MQUEUE_NAME "/_rtoax_mq_"
#define MSG_FILE "/etc/os-release"

#define MQUEUE_MAX_SIZE 128
#define MQUEUE_MAX_MSG 256

#define MSGQ_TYPE   888

#ifndef offsetof
#define offsetof(type, number) __builtin_offsetof(type, number)
#endif

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define log_send(fmt...) do { \
		printf("\033[33m[%d]", pthread_self()); \
		printf(fmt); \
		printf("\033[m"); \
	} while (0)
#define log_recv(fmt...) do { \
		printf("\033[32m[%d]", pthread_self()); \
		printf(fmt); \
		printf("\033[m"); \
	} while (0)


struct dbg_msg {
	unsigned long msg_seq;
	unsigned long msg_ack;
	unsigned long msg_len;
	unsigned long ns;
	char data[];
};

struct msg_operation {
	const char *name;
	int (*init)(void);
	void (*close)(void);
	ssize_t (*recv)(void *msg_ptr, size_t msg_len);
	int (*send)(void *msg_ptr, size_t msg_len);
};

mqd_t mqd;
int msqid;

static inline unsigned long nsecs(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000000000UL + ts.tv_nsec;
}

int __hook_mqueue_init(void)
{
	struct mq_attr attr;

	mq_unlink(MQUEUE_NAME);

	attr.mq_flags = 0;
	attr.mq_msgsize = MQUEUE_MAX_SIZE;

	attr.mq_maxmsg = MQUEUE_MAX_MSG;
	mqd = mq_open(MQUEUE_NAME, O_RDWR|O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO, &attr);
	if (mqd == -1) {
		printf("mq_open failed, %d, %s\n", mqd, strerror(errno));
		exit(1);
	}
	return 0;
}

ssize_t __hook_mq_receive(void *msg_ptr, size_t msg_len)
{
	return mq_receive(mqd, msg_ptr, msg_len, 0);
}

int __hook_mq_send(void *msg_ptr, size_t msg_len)
{
	return mq_send(mqd, (char*)msg_ptr, msg_len, 0);
}

int __hook_msgq_init(void)
{
	key_t key;

	if ((key = ftok(MSG_FILE, 123)) < 0) {
		perror("ftok error");
		exit(1);
	}

	if((msqid = msgget(key, IPC_CREAT | 0777)) == -1) {
		perror("msgget error");
		exit(1);
	}
	return 0;
}

ssize_t __hook_msgrcv(void *msg_ptr, size_t msg_len)
{
	return msgrcv(msqid, msg_ptr, msg_len, MSGQ_TYPE, 0);
}

int __hook_msgsnd(void *msg_ptr, size_t msg_len)
{
	return msgsnd(msqid, msg_ptr, msg_len, 0);
}

struct msg_operation operations[] = {
	{
		.name = "PosixMQ",
		.init = __hook_mqueue_init,
		.recv = __hook_mq_receive,
		.send = __hook_mq_send,
	},
	{
		.name = "SysvMQ",
		.init = __hook_msgq_init,
		.recv = __hook_msgrcv,
		.send = __hook_msgsnd,
	},
};

void printf_rate(struct msg_operation *o, const char *prefix,
		 unsigned long bytes, unsigned long ns)
{
	printf("%-8s : %s rate %.3lf Mbits/sec\n",
		o->name,
		prefix, bytes * 8.0 / 1024 / 1024 * 1000000000 / ns);
}

void *task_send_fn(void *arg)
{
	int ret;
	char send_buffer[MQUEUE_MAX_SIZE] ={'A'};
	struct dbg_msg *send_pdmsg = (struct dbg_msg *)&send_buffer;
	struct msg_operation *o = arg;

	unsigned long nloop = 0;

	unsigned long start, end;
	unsigned long send_bytes = 0;

	memset(send_buffer, 'A', sizeof(send_buffer));

	send_pdmsg->msg_seq = MSGQ_TYPE;
	send_pdmsg->msg_ack = 0;
	send_pdmsg->msg_len = sizeof(send_buffer);

	start = nsecs();

	while (++nloop <= NR_MSG) {
		send_pdmsg->ns = nsecs();
		ret = o->send((char*)send_pdmsg, send_pdmsg->msg_len);
		if (ret != 0) {
			continue;
		} else {
			send_bytes += send_pdmsg->msg_len;
			send_pdmsg->msg_ack++;
		}
	}
	end = nsecs();
	printf_rate(o, "TX", send_bytes, end - start);
	pthread_exit(NULL);
}

void *task_recv_fn(void *arg)
{
	ssize_t n;
	char buffer[MQUEUE_MAX_SIZE] ={0};

	struct dbg_msg *pdmsg;
	unsigned long nloop = 0;
	unsigned long start, end;
	unsigned long recv_bytes = 0;
	unsigned long ns_total = 0;
	struct msg_operation *o = arg;

	start = nsecs();

	while (++nloop <= NR_MSG) {
		n = o->recv(buffer, MQUEUE_MAX_SIZE);
		if (n <= 0) {
			continue;
		} else {
			recv_bytes += n;
			pdmsg = (struct dbg_msg*)buffer;
			ns_total += nsecs() - pdmsg->ns;
			pdmsg->msg_ack++;

		}
	}
	end = nsecs();

	printf("%-8s : Latency Per Message = %lf ns\n",
		o->name,
		ns_total * 1.0 / (nloop - 1));
	printf_rate(o, "RX", recv_bytes, end - start);
	pthread_exit(NULL);
}

int main(void)
{
	int i;
	struct msg_operation *o;
	pthread_t task1, task2;

	for (i = 0; i < ARRAY_SIZE(operations); i++) {
		o = &operations[i];
		if (o->init)
			o->init();
	}

	for (i = 0; i < ARRAY_SIZE(operations); i++) {
		o = &operations[i];
		pthread_create(&task1, NULL, task_send_fn, o);
		pthread_create(&task2, NULL, task_recv_fn, o);
		pthread_join(task1, NULL);
		pthread_join(task2, NULL);
	}

	for (i = 0; i < ARRAY_SIZE(operations); i++) {
		o = &operations[i];
		if (o->close)
			o->close();
	}
	return 0;
}

