#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

unsigned int alarm_self(unsigned int seconds)
{
	struct itimerval old, new;
	new.it_interval.tv_usec = 0;
	new.it_interval.tv_sec = 0;
	new.it_value.tv_usec = 0;
	new.it_value.tv_sec = (long int) seconds;

	alarm(1);

	printf("alarm_self.\n");

	if (setitimer(ITIMER_REAL, &new, &old) < 0)
		return 0;
	else
		return old.it_value.tv_sec;
}

void printmsg(int sig)
{
	printf("Hello world\n");
	alarm(1);
	return ;
}

int main(void)
{
	signal(SIGALRM, printmsg);

	alarm(1);

	printf("Wait.\n");

	getchar();

	return 0;
}
