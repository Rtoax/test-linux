#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/timerfd.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define TFMT "[%ld,%ld]"
#define T(t) t.tv_sec, t.tv_nsec

void sig_handler(int signum)
{
	printf("signal handler.\n");
	exit(0);
	return;
}

int main(void)
{
	int ret;
	uint64_t exp = 0;
	struct itimerspec t1 = { { 1, 0 }, { 1, 0 } }, t2;

	signal(SIGINT, sig_handler);

	int timerfd = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC);
	printf("Timer FD: %d\n", timerfd);

	ret = timerfd_settime(timerfd, 0, &t1, &t2);
	printf("[%d, new]: " TFMT "," TFMT "\n", ret, T(t1.it_interval),
	       T(t1.it_value));
	printf("[%d, old]: " TFMT "," TFMT "\n", ret, T(t2.it_interval),
	       T(t2.it_value));

	ret = timerfd_gettime(timerfd, &t1);
	printf("[%d, get]: " TFMT "," TFMT "\n", ret, T(t1.it_interval),
	       T(t1.it_value));

	while (1) {
		read(timerfd, &exp, sizeof(exp));

		printf("exp  =%ld\n", exp);
		close(timerfd);
		break;
	}

	return 0;
}
