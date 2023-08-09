#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


void catch_fun(int signo)
{
	printf("catch signal\n");
}

int main()
{
	int ret;
	struct itimerval sa;

	sa.it_value.tv_sec = 1;
	sa.it_value.tv_usec = 0;
	sa.it_interval.tv_sec = 2;
	sa.it_interval.tv_usec = 0;

	signal(SIGALRM, catch_fun);

	/* ITIMER_REAL: At each expiration, a SIGALRM signal is generated */
	ret = setitimer(ITIMER_REAL, &sa, NULL);
	if (ret == -1) {
		perror("setitimer\n");
		exit(1);
	}

	while (1)
		sleep(1);

	return 0;
}
