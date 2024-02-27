#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <pthread.h>
#include <unistd.h>

#include "shmq.h"

#define DEV_NAME	"/dev/"SHMQ_DEV_NAME

static void *task1(void*arg)
{
	int fd;
	char val[]={"abc hello world"};
	int ret;

	fd = open(DEV_NAME, O_RDWR);
	if (fd < 0) {
		printf("task1: write: can't open %s \n", DEV_NAME);
		return NULL;
	}

	printf("task1: write: fd = %d\n", fd);

	fsync(fd);

	flock(fd, LOCK_EX);

	ret = ioctl(fd, SHMQ_IOC_WAKE_UP);
	printf("task1: write: ioctl: ret = %d\n", ret);

	while (1) {
		sleep(1);
		val[0] += 1;
		ret = write(fd, val, sizeof(val));
		printf("task1: write: ret = %d, val = %s\n", ret, val);
	}

	return NULL;
}

static void *task2(void*arg)
{
	int fd;
	char val[256]={0};
	int ret;

	fd = open(DEV_NAME, O_RDWR);
	if (fd < 0) {
		printf("task2: read: can't open %s \n", DEV_NAME);
		return NULL;
	}

	printf("task2: read: fd = %d\n", fd);

	while (1) {
		ret = read(fd, val, sizeof(val));
		printf("task2: read: ret = %d, val = %s\n", ret, val);
	}

	return NULL;
}

int main(void)
{
	printf("Create 2 thread to test the shmq.\n");

	pthread_t t1, t2;
	pthread_create(&t1, NULL, &task1, NULL);
	pthread_create(&t2, NULL, &task2, NULL);

	printf("Sys running...\n");

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}

