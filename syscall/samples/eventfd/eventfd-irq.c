#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/eventfd.h>

#include "utils.h"

int efd = 0;

unsigned long latency = 0;
unsigned long total_latency = 0;
unsigned long total_num = 0;

int irq_init(int flags)
{
	return eventfd(0, flags);
}

int irq_trigger(int irqfd)
{
	return eventfd_write(irqfd, 1);
}

uint64_t irq_wait(int irqfd)
{
	eventfd_t cnt;
	eventfd_read(irqfd, &cnt);
	return cnt;
}

void *write_task(void *arg)
{
	int ret;
	unsigned long count = 0, failed = 0;

	while (1) {
		ret = irq_trigger(efd);
		if (ret < 0) {
			failed++;
			continue;
		}
		if (++count == 3000000) {
			log_enqueue("enqueue = %ld, failed = %ld\n", count,
				    failed);
			count = 0;
		}
	}
	pthread_exit(NULL);
}

void *read_task(void *arg)
{
	eventfd_t count;

	while (1) {
		sleep(1);
		count = irq_wait(efd);
		if (count < 0)
			break;
		log_dequeue("dequeue = %ld\n", count);
	}
	pthread_exit(NULL);
}

void demo_flags(int flags)
{
	pthread_t write_taskid, read_taskid;

	efd = irq_init(flags);

	pthread_create(&write_taskid, NULL, write_task, NULL);
	pthread_create(&read_taskid, NULL, read_task, NULL);

	pthread_join(write_taskid, NULL);
	pthread_join(read_taskid, NULL);

	printf("Exit.\n");
	close(efd);
}

int main(int argc, char *argv[])
{
	int flags;

	flags = parse_flags(argc, argv);

	demo_flags(flags);

	return EXIT_SUCCESS;
}
