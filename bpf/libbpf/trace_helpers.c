// SPDX-License-Identifier: GPL-3.0
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define TRACEFS_PIPE    "/sys/kernel/tracing/trace_pipe"
#define DEBUGFS_PIPE    "/sys/kernel/debug/tracing/trace_pipe"

static pthread_t thread;

/**
 * cb: call back, if return non-zero value, while done
 */
static int read_trace_pipe_cb(int (*cb)(const char *str, void *arg), void *arg)
{
	size_t buflen, n, i;
	char *pipefile, *buf;
	FILE *fp;
	int err, sfd;
	sigset_t sigmask;
	struct pollfd pfds[2];

	if (access(TRACEFS_PIPE, F_OK) == 0)
		pipefile = TRACEFS_PIPE;
	else
		pipefile = DEBUGFS_PIPE;

	fp = fopen(pipefile, "r");
	if (!fp) {
		fprintf(stderr, "failed to open %s\n", pipefile);
		return -errno;
	}

	buf = NULL;

	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGUSR1);
	pthread_sigmask(SIG_BLOCK, &sigmask, NULL);

	sfd = signalfd(-1, &sigmask, 0);

	pfds[0].fd = fileno(fp);
	pfds[0].events = POLLIN;
	pfds[1].fd = sfd;
	pfds[1].events = POLLIN;

	/**
	 * If signal(2) does not process the signal, the process will exit
	 * directly from the loop, and the return code will not be executed.
	 */
	while (true) {
		n = poll(pfds, 2, -1);
		if (n <= 0)
			continue;

		for (i = 0; i < 2; i++) {
			if (pfds[i].revents == 0)
				continue;
			if (pfds[i].fd == fileno(fp)) {
				n = getline(&buf, &buflen, fp);
				if (n < 0 && errno != EAGAIN)
					break;

				err = cb(buf, arg);
				if (err)
					break;
			/**
			 * Use signal to terminate reading trace_pipe.
			 */
			} else if (pfds[i].fd == sfd) {
				struct signalfd_siginfo fdsi;

				n = read(sfd, &fdsi, sizeof(fdsi));
				psignal(fdsi.ssi_signo, "read_trace_pipe terminate");
				goto close;
			}
		}
	}

close:
	free(buf);
	fclose(fp);
	close(sfd);
	return 0;
}

static int trace_pipe_printf(const char *str, void *arg)
{
	printf("%s", str);
	return 0;
}

static void *thread_read_trace_pipe(void *arg)
{
	read_trace_pipe_cb(trace_pipe_printf, NULL);
	return NULL;
}

int read_trace_pipe_start(void)
{
	static int init = 0;
	if (++init > 1) {
		fprintf(stderr, "read_trace_pipe is non-reentrant function.\n");
		return -1;
	}
	pthread_create(&thread, NULL, thread_read_trace_pipe, NULL);
	return 0;
}

int read_trace_pipe_wait(void)
{
	pthread_join(thread, NULL);
}

int read_trace_pipe(void)
{
	read_trace_pipe_start();
	read_trace_pipe_wait();
}

int stop_read_trace_pipe(void)
{
	return pthread_kill(thread, SIGUSR1);
}

int print_bpf_log_buf(char *buf, size_t size)
{
	int i;

	for (i = 0; i < size; i++) {
		if (buf[i] == 0 && buf[i + 1] == 0)
			break;
		printf("%c", buf[i]);
	}
	return 0;
}
