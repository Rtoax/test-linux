#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>

#include "utils.h"

#define MAX_EVENTS 64

static pthread_t tpipe_in1;
static pthread_t tpipe_in2;
static pthread_t tpipe_in3;
static pthread_t tpipe_in4;
static pthread_t tpipe_in5;
static pthread_t tpipe_out;

static int pipe_fd[2] = {-1};

static FILE *pipe_in_fp = NULL;
static FILE *pipe_out_fp = NULL;

static int epoll_fd = -1;

static struct epoll_event epoll_evs[MAX_EVENTS];

static volatile size_t pkg_size = 10;

FILE *record_rate_fp = NULL;

int nr_thread_write = 1;
int max_pkg_size = 10000;
int pkg_size_interval = 20;


int mysendto(void *buf, size_t size)
{
	return write(fileno(pipe_in_fp), buf, size);
}

void *thread_pipe_in(void*arg)
{
	char threadname[16];
	unsigned long int tid = pthread_self();
	pthread_getname_np(tid, threadname, 16);

	while (1) {
		static char buf[1500] = {0};
		mysendto(buf, pkg_size);
	}
}

int pipe_out_loop(void *arg)
{
	static char buffer[8192] = {0};
	int nr_events = 0, iev;

	static long int npkg = 0;
	static long int nbyte = 0;
	static struct timeval timestart = {0,0};
	static struct timeval timeend = {0,0};

	static int start_flag = 0;

	nr_events = epoll_wait(epoll_fd, epoll_evs, MAX_EVENTS, -1);

	for (iev = 0; iev < nr_events; iev++) {
		if (epoll_evs[iev].data.fd == fileno(pipe_out_fp) && \
			epoll_evs[iev].events & EPOLLIN) {

			int n = read(fileno(pipe_out_fp), buffer, sizeof(buffer));
			if (start_flag == 0) {
				gettimeval(&timestart);
			}
			start_flag = 1;
			npkg++;
			nbyte+=n;
		}
	}

	gettimeval(&timeend);

	if (npkg % 100000 == 0) {
		static char description[256] = {0};
		static double Mbps = 0.0;

		sprintf(description, "PIPE PKG Size %4ld", pkg_size);
		Mbps = statistic_throughput(description, &timestart, &timeend, nbyte, npkg);

		fprintf(record_rate_fp, "%8ld		%10.2lf\n", pkg_size, Mbps);
		fflush(record_rate_fp);

		memset(&timestart, 0, sizeof(struct timeval));
		memset(&timeend, 0, sizeof(struct timeval));
		start_flag = 0;
		npkg = nbyte = 0;

		pkg_size += pkg_size_interval;

		if (pkg_size > max_pkg_size) {
			exit(1);
		}
	}
	return 0;
}

void *thread_pipe_out(void *arg)
{
	while (1)
		pipe_out_loop(NULL);
}

void thread_execute(void)
{
	if (nr_thread_write >= 1)
		pthread_create(&tpipe_in1, NULL, thread_pipe_in, NULL);
	if (nr_thread_write >= 2)
		pthread_create(&tpipe_in2, NULL, thread_pipe_in, NULL);
	if (nr_thread_write >= 3)
		pthread_create(&tpipe_in3, NULL, thread_pipe_in, NULL);
	if (nr_thread_write >= 4)
		pthread_create(&tpipe_in4, NULL, thread_pipe_in, NULL);
	if (nr_thread_write >= 5)
		pthread_create(&tpipe_in5, NULL, thread_pipe_in, NULL);

	pthread_create(&tpipe_out, NULL, thread_pipe_out, NULL);

	if (nr_thread_write >= 1)
		pthread_setname_np(tpipe_in1, "pipe-in1");
	if (nr_thread_write >= 2)
		pthread_setname_np(tpipe_in2, "pipe-in2");
	if (nr_thread_write >= 3)
		pthread_setname_np(tpipe_in3, "pipe-in3");
	if (nr_thread_write >= 4)
		pthread_setname_np(tpipe_in4, "pipe-in4");
	if (nr_thread_write >= 5)
		pthread_setname_np(tpipe_in5, "pipe-in5");

	pthread_setname_np(tpipe_out, "pipe-out");
}

void epoll_initial(void)
{
	epoll_fd = epoll_create(1);
	struct epoll_event pipe_ev;
	pipe_ev.data.fd = fileno(pipe_out_fp);
	pipe_ev.events = EPOLLIN;
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fileno(pipe_out_fp), &pipe_ev);
}

int main(int argc, char *argv[]) {

	if (argc < 5) {
		printf("%s [nthread] [max-pkg-size] [pkg-size-interval] [record-file-name] .\n", argv[0]);
		exit(1);
	} else {
		nr_thread_write = atoi(argv[1]);
		max_pkg_size = atoi(argv[2]);
		pkg_size_interval = atoi(argv[3]);
	}

	record_rate_fp = fopen(argv[4], "w");

	pipe(pipe_fd);

	pipe_in_fp = fdopen(pipe_fd[1], "w");
	pipe_out_fp = fdopen(pipe_fd[0], "r");

	epoll_initial();

	thread_execute();

	while (1) {
		sleep(1);
		/* do nothing */
	}

	return 0;
}
