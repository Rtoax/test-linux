#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/signalfd.h>


#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
	sigset_t mask;
	int sfd;
	struct signalfd_siginfo fdsi;
	ssize_t s;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);

	/* 阻塞信号以使得它们不被默认的处理试方式处理 */

	if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
		handle_error("sigprocmask");

	sfd = signalfd(-1, &mask, 0);
	if (sfd == -1)
		handle_error("signalfd");

	for (;;) {
		s = read(sfd, &fdsi, sizeof(struct signalfd_siginfo));
		if (s != sizeof(struct signalfd_siginfo))
			handle_error("read");

		switch (fdsi.ssi_signo) {
		case SIGINT:
			printf("Got SIGINT\n");
			goto exit;
			break;
		case SIGQUIT:
			printf("Got SIGQUIT\n");
			goto exit;
			break;
		default:
			printf("Read unexpected signal\n");
			break;
		}
	}

exit:
	close(sfd);
	return 0;
}
