#include <stdio.h>
#include <signal.h>

#include "libs/memshow.h"

int main(void)
{
	sigset_t st;

	sigemptyset(&st);
	fhexdump(stdout, "Empty: ", &st, sizeof(st));

	sigaddset(&st, SIGINT);
	sigaddset(&st, SIGSTOP);
	fhexdump(stdout, "  Add: ", &st, sizeof(st));

	sigdelset(&st, SIGINT);
	fhexdump(stdout, "  Del: ", &st, sizeof(st));

	sigfillset(&st);
	fhexdump(stdout, " Fill: ", &st, sizeof(st));

	if (sigismember(&st, SIGSTOP)) {
		printf("Setted SIGSTOP\n");
	}

	return 0;
}
