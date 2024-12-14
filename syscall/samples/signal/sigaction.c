#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void timeout(int signo)
{
	if (signo == SIGALRM) {
		printf("time out! \n");
		alarm(1);
	}
}

int main(void)
{
	int i;
	struct sigaction act;

	act.sa_handler = timeout;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGALRM, &act, 0);

	alarm(1);

	for (i = 0; i < 3; i++)
		sleep(100);

	return 0;
}
