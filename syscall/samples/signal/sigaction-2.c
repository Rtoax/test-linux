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
	struct sigaction s1 = {
		.sa_handler = handler,
		.sa_flags = SA_RESTART,
	}, s2;
	sigaction(SIGINT, &s1, &s2);
}

void demo2(void)
{
	struct sigaction new_action, old_action;

	/* Set up the structure to specify the new action. */
	new_action.sa_handler = handler;

	sigemptyset(&new_action.sa_mask);

	new_action.sa_flags = 0;

	sigaction(SIGINT, NULL, &old_action);

	if (old_action.sa_handler != SIG_IGN)
		sigaction(SIGINT, &new_action, NULL);
	sigaction(SIGHUP, NULL, &old_action);

	if (old_action.sa_handler != SIG_IGN)
		sigaction(SIGHUP, &new_action, NULL);
	sigaction(SIGTERM, NULL, &old_action);

	if (old_action.sa_handler != SIG_IGN)
		sigaction(SIGTERM, &new_action, NULL);

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

