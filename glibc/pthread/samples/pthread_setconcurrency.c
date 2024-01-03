/**
 * pthread_setconcurrency() 函数在linux下，如果你忽略了这个函数的使用，那么能够并发的线程
 * 数目由实现者来控制，对于系统调度的效率而言往往不是什么好的事情，因为默认的设置往往不是最佳的。
 * 更为糟糕的是，如果在某些系统中，如果你不调用 pthread_setconcurrency() 函数，那么系统中
 * 的运行的线程仅仅是第一个被创建的线程，其他线程根本不会被运行。比如在 solaris 2.6 中就有这
 * 些情况。为了在unix或者是linux系统上使移植更加的容易，请不要忘记在适当的地方调用次函数，清晰
 * 的告诉系统我们使用的线程个数。虽然在某些系统上，这个调用是徒劳的，但是它的使用增强的移植性！
 */
#include <stdio.h>
#ifndef __USE_UNIX98
#define __USE_UNIX98
#endif
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sched.h>

#define MAXITEMS	(100 * 10000)
#define MAXTHREADS	(100)
#define min(a, b)	(a < b ? a : b)

int nitems;

struct {
	pthread_mutex_t mutex;
	int buff[MAXITEMS];
	int nput;
	int nval;
} shared = { PTHREAD_MUTEX_INITIALIZER };

struct Node {
	int count;
	int num;
};

void *producer(void *arg)
{
	struct Node *p = (struct Node *)arg;
	printf("producer: num[%d] = %d\n", p->num, p->count);

	while (1) {
		pthread_mutex_lock(&shared.mutex);
		if (shared.nput >= nitems) {
			pthread_mutex_unlock(&shared.mutex);
			return NULL;
		}

		shared.buff[shared.nput] = shared.nval;
		++shared.nput;
		++shared.nval;
		pthread_mutex_unlock(&shared.mutex);
		p->count++;
	}
}

void *consumer(void *arg)
{
	int i;
	for (i = 0; i < nitems; ++i) {
		if (shared.buff[i] != i)
			printf("consumer: buff[%d] = %d\n", i, shared.buff[i]);
	}

	return NULL;
}

int main(int argc, char **argv)
{
	int i, nthreads;
	struct Node count[MAXTHREADS];
	int level;
	pthread_t tid_producer[MAXTHREADS], tid_consumer;

	if (argc != 3) {
		printf("usage: %s [items] [threads]\n", argv[0]);
		exit(0);
	}

	nitems = min(atoi(argv[1]), MAXITEMS);
	nthreads = min(atoi(argv[2]), MAXTHREADS);

	printf("nitems = %d, nthreads = %d\n", nitems, nthreads);

	/* for more CPUS, must bind to one cpu */
	level = pthread_getconcurrency();
	printf("getconcurrency = %d\n", level);

	if (pthread_setconcurrency(nthreads) != 0) {
		printf("setconcurrency error: %d, %s\n", errno,
		       strerror(errno));
		exit(0);
	} else {
		level = pthread_getconcurrency();
		printf("after set = %d, getconcurrency = %d\n", nthreads,
		       level);
	}

	for (i = 0; i < nthreads; ++i) {
		count[i].num = i;
		count[i].count = 0;
		if (pthread_create(&tid_producer[i], NULL, producer, &count[i])
		    != 0) {
			printf("create pthread %d error: %d,%s\n", i, errno,
			       strerror(errno));
			exit(0);
		}
	}

	for (i = 0; i < nthreads; ++i) {
		pthread_join(tid_producer[i], NULL);
		printf("producer exit: num[%d] = %d\n", count[i].num,
		       count[i].count);
	}

	pthread_create(&tid_consumer, NULL, consumer, NULL);
	pthread_join(tid_consumer, NULL);
	return 0;
}
