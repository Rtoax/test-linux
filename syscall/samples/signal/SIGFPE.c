#include <stdlib.h>
#include <signal.h>
#include <stdio.h>


void sig_handler(int signum)
{
	psignal(signum, "SIGFPE");
	exit(0);
}

int main(int argc, char*argv[])
{
	printf("NSIG = %d\n", NSIG);
	printf("SIGFPE = %d\n", SIGFPE);

	signal(SIGFPE, sig_handler);

	int a = 0;
	int __attribute__((unused)) b = 1 / a;

	return 0;
}
