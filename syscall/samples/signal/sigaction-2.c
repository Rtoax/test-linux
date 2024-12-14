#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


void handler(int signum)
{
	printf("%d\n", signum);
	psignal(signum, "RongTao");
	exit(0);
}

void demo1(void)
{
	struct sigaction new, old;
	new.sa_handler = handler,
	new.sa_flags = SA_RESTART,
	sigaction(SIGINT, &new, &old);
}

void demo2(void)
{
	struct sigaction new, old;

	/* Set up the structure to specify the new action. */
	new.sa_handler = handler;
	sigemptyset(&new.sa_mask);
	new.sa_flags = 0;

	sigaction(SIGINT, NULL, &old);

	if (old.sa_handler != SIG_IGN)
		sigaction(SIGINT, &new, NULL);
	sigaction(SIGHUP, NULL, &old);

	if (old.sa_handler != SIG_IGN)
		sigaction(SIGHUP, &new, NULL);
	sigaction(SIGTERM, NULL, &old);

	if (old.sa_handler != SIG_IGN)
		sigaction(SIGTERM, &new, NULL);
}

void demo3(void)
{
	struct sigaction temp;

	sigaction(SIGHUP, NULL, &temp);

	if (temp.sa_handler != SIG_IGN) {
		temp.sa_handler = handler;
		sigemptyset(&temp.sa_mask);
		sigaction(SIGHUP, &temp, NULL);
	}
}

int main(void)
{
	demo2();
	demo3();
	while(1);
	return 0;
}

