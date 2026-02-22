#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void sig_handler(int sig)
{
	psignal(sig, "Catch");
	exit(1);
}

int overflow(void)
{
	char *s = NULL;
	char c = s[1024];
	return c;
}

int main(int argc, char *argv[])
{
	int i;

	fprintf(stderr, "usage: %s [catch=<segv>]\n", argv[0]);

	for (i = 1; i < argc; i++) {
		if (!strncmp("catch=", argv[i], strlen("catch="))) {
			if (!strcmp(argv[i] + strlen("catch="), "segv")) {
				/**
				 * If catching segv, the core will not be
				 * generated, except restore the signal handler
				 * in sig_handler().
				 */
				signal(SIGSEGV, sig_handler);
			}
		}
	}

	overflow();
	return 0;
}
