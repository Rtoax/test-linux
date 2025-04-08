#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/eventfd.h>

#include "utils.h"

int efd = 0;

unsigned long latency = 0;

void *write_task(void *arg)
{
	int ret;
	eventfd_t count = 1;

	while (1) {
		latency = get_nsecs();
		ret = eventfd_write(efd, count);
		if (ret < 0)
			continue;
	}
	pthread_exit(NULL);
}

void *read_task(void *arg)
{
	int ret;
	eventfd_t count;
	unsigned long total_latency = 0;
	unsigned long total_num = 0;

	while (1) {
		ret = eventfd_read(efd, &count);
		if (ret < 0) {
			log_dequeue("read error ret = %d, count = %ld\n", ret,
				    count);
			break;
		}
		total_latency += get_nsecs() - latency;
		total_num++;

		if (total_num % 100000 == 0)
			printf
			    ("latency. per msgs \033[1;31m%lf ns\033[m, msgs (total %ld).\n",
			     total_latency * 1.0 / total_num, total_num);
		count = 0;
	}
	pthread_exit(NULL);
}

void demo_flags(int inival, int flags)
{
	pthread_t write_taskid, read_taskid;

	efd = eventfd(inival, flags);

	pthread_create(&write_taskid, NULL, write_task, NULL);
	pthread_create(&read_taskid, NULL, read_task, NULL);

	pthread_join(write_taskid, NULL);
	pthread_join(read_taskid, NULL);

	printf("Exit.\n");
	close(efd);
}

int main(void)
{
	demo_flags(0, EFD_CLOEXEC | EFD_SEMAPHORE);
	return EXIT_SUCCESS;
}
