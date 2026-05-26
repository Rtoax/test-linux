#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

void sig_handler(int signum)
{
	switch (signum) {
	case SIGPIPE:
		fprintf(stderr, "Catch Broken Pipe signal.\n");
		break;
	default:
		break;
	}
}

int main(void)
{
	int pipe_fd[2] = {0};

	signal(SIGPIPE, sig_handler);

	pipe(pipe_fd);

	/* close read peer */
	close(pipe_fd[0]);
	/* write to write peer, trigger SIGPIPE signal. */
	write(pipe_fd[1], "Hello", 5);
	close(pipe_fd[1]);

	return 0;
}
