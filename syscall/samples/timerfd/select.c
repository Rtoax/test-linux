#include <stdio.h>
#include <sys/select.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/timerfd.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define N_TIMER 3

static int timersfd[N_TIMER] = { 0 };

void sig_handler(int signum)
{
	printf("signal handler.\n");
	exit(0);
}

int main(void)
{
	int maxfd = 0, nready = 0;
	int i;
	uint64_t exp = 0;
	struct itimerspec t1 = { { 1, 0 }, { 1, 0 } };
	fd_set readtimersfd;

	FD_ZERO(&readtimersfd);

	signal(SIGINT, sig_handler);

	for (i = 0; i < N_TIMER; i++) {
		timersfd[i] = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC);
		timerfd_settime(timersfd[i], 0, &t1, NULL);
		printf("timerfd = %d\n", timersfd[i]);
		FD_SET(timersfd[i], &readtimersfd);
		if (maxfd < timersfd[i])
			maxfd = timersfd[i];
	}
	printf("maxfd = %d\n", maxfd);

	while (1) {
		fd_set allset = readtimersfd;
		static int count = 0;
		nready = select(maxfd + 1, &allset, NULL, NULL, NULL);
		printf("nready = %d, count = %d\n", nready, count++);
		for (i = 0; i < N_TIMER; i++) {
			if (FD_ISSET(timersfd[i], &allset)) {
				read(timersfd[i], &exp, sizeof(exp));
				printf("exp = %ld\n", exp);
				if (timersfd[i] == 4)
					FD_CLR(timersfd[i], &readtimersfd);
			}
		}
	}

	return 0;
}
