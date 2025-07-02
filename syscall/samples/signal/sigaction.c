#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


void sig_alarm_timeout(int signo)
{
	if (signo == SIGALRM) {
		printf("time out! \n");
		alarm(1);
	}
}

void sig_handler_exit(int signum)
{
	psignal(signum, "EXIT");
	exit(0);
}

void tst_getaction(void)
{
	struct sigaction temp;

	sigaction(SIGHUP, NULL, &temp);

	if (temp.sa_handler != SIG_IGN) {
		temp.sa_handler = sig_handler_exit;
		sigemptyset(&temp.sa_mask);
		sigaction(SIGHUP, &temp, NULL);
	}
}

void tst_alarm(void)
{
	int i;
	struct sigaction act;

	act.sa_handler = sig_alarm_timeout;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGALRM, &act, 0);

	alarm(1);

	for (i = 0; i < 3; i++)
		sleep(100);
}

int main(void)
{
	tst_getaction();
	tst_alarm();
	return 0;
}
