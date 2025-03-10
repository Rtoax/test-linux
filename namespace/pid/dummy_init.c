#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int signo)
{
	psignal(signo, "Ignore ");
}

int main(void) 
{
	signal(SIGTERM, sig_handler);
	signal(SIGINT, sig_handler);
	/* SIGKILL can't be catched */
	signal(SIGKILL, sig_handler);
	while (1) {
		pause();
	}
	return 0;
}
