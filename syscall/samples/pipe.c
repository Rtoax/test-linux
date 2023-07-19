#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <errno.h>


int pipe_fd[2] = {0};
FILE *pipe_fp[2];

void sig_handler(int signum)
{
	switch (signum) {
	case SIGPIPE:
		fprintf(stderr, "Broken Pipe.\n");
		break;
	default:
		break;
	}
}

void *task_fn(void *arg)
{
	fprintf(pipe_fp[1], "Hello, world.\n");
	fclose(pipe_fp[1]);
	return NULL;
}

int main(void)
{
	char ch;

	signal(SIGPIPE, sig_handler);

	pipe(pipe_fd);
	pipe_fp[0] = fdopen(pipe_fd[0], "r");
	pipe_fp[1] = fdopen(pipe_fd[1], "w");

	pthread_t task;
	pthread_create(&task, NULL, task_fn, NULL);

	while ((ch = fgetc(pipe_fp[0])) != EOF) {
		putchar(ch);
	}
	fclose(pipe_fp[0]);

	pthread_join(task, NULL);

	/* Double close: Bad file descriptor */
	close(pipe_fd[0]);
	if (errno != EBADF)
		fprintf(stderr, "ERROR: close() should return EBADF here.\n");
	close(pipe_fd[1]);
	if (errno != EBADF)
		fprintf(stderr, "ERROR: close() should return EBADF here.\n");

	/* Test Broken Pipe, trigger SIGPIPE signal. */
	pipe(pipe_fd);
	/* close read peer */
	close(pipe_fd[0]);
	/* write to write peer, trigger SIGPIPE signal. */
	write(pipe_fd[1], "Hello", 5);
	close(pipe_fd[1]);

	return 0;
}
