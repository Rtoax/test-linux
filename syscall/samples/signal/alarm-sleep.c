#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>


void catch_fun(int signo)
{
	printf("Catch alarm.\n");
}

unsigned int alarm_sleep(unsigned int seconds)
{
	int ret = 0;

	struct sigaction act, oldact;

	act.sa_handler = catch_fun;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	ret = sigaction(SIGALRM, &act, &oldact);
	if (ret == -1) {
		perror("sigaction\n");
		exit(1);
	}

	/* pause + alarm = sleep */
	alarm(seconds);
	ret = pause();

	/* interrupted by signal */
	if (ret == -1 && errno == EINTR) {
		printf("interrupt pause\n");
	}

	int old = alarm(0);
	/* restore old sigaction */
	sigaction(SIGALRM, &oldact, NULL);

	return old;
}

int main(void)
{
	int i = 3;
	while (i--) {
		printf("====mysleep====\n");
		alarm_sleep(1);
	}
	return 0;
}

