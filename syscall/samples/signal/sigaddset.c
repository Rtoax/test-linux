#include <stdio.h>
#include <signal.h>

#include "libs/memshow.h"


int main(void)
{
    sigset_t st;

    sigemptyset(&st);
	memshow("Empty: ", &st, sizeof(st));

    sigaddset(&st, SIGINT);
    sigaddset(&st, SIGSTOP);
	memshow("  Add: ", &st, sizeof(st));

	sigdelset(&st, SIGINT);
	memshow("  Del: ", &st, sizeof(st));

	sigfillset(&st);
	memshow(" Fill: ", &st, sizeof(st));

	if (sigismember(&st, SIGSTOP)) {
		printf("Setted SIGSTOP\n");
	}

    return 0;
}
