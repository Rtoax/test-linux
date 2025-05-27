#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <getopt.h>
#include <syscall.h>

#include "flock_helpers.h"

/* FIXME: In some glibc, there is no gettid() */
int sys_gettid(void)
{
	return syscall(__NR_gettid);
}
#define gettid() sys_gettid()

static const char *filename = "testfile";
static int try_times = 10;
static int nr_threads = 2;

void usage(int err)
{
	printf("-h, --help      show this information\n"
	       "-f, --file      specify file to lock, default: %s\n"
	       "-n, --times     try times to get file lock, default: %d\n"
	       "-t, --threads   number of parallel threads, default: %d\n",
	       filename, try_times, nr_threads);

	exit(err);
}

void *task_routinue(void *arg)
{
	int try = try_times;
	char buffer[1024];

	snprintf(buffer, sizeof(buffer), "I am process %d's thread %d\n",
		 getpid(), gettid());
	printf("%s", buffer);

	while (try-- && !open_and_write_with_lock(filename, "Thread", buffer));

	return NULL;
}

int main(int argc, char *argv[])
{
	int i, fd;
	pthread_t *threads;
	int cmd, option_index;

	static struct option options[] = {
		{"help", no_argument, 0, 'h'},
		{"file", required_argument, 0, 'f'},
		{"times", required_argument, 0, 'n'},
		{"threads", required_argument, 0, 't'},
		{0, 0, 0, 0}
	};

	while (1) {
		cmd =
		    getopt_long(argc, argv, "hf:t:n:", options, &option_index);
		if (cmd == -1)
			break;
		switch (cmd) {
		case 'h':
			usage(0);
			break;
		case 'f':
			filename = optarg;
			break;
		case 'n':
			try_times = atoi(optarg);
			break;
		case 't':
			nr_threads = atoi(optarg);
			break;
		default:
			abort();
			break;
		}
	}

	if (nr_threads <= 0) {
		fprintf(stderr, "Invalid thread number %d\n", nr_threads);
		exit(1);
	}

	threads = malloc(sizeof(pthread_t) * nr_threads);

	/* Create the testfile. */
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	write(fd, "hello\n", sizeof("hello\n"));
	close(fd);

	for (i = 0; i < nr_threads; i++) {
		pthread_create(&threads[i], NULL, task_routinue, NULL);
	}

	for (i = 0; i < nr_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	free(threads);
	return 0;
}
