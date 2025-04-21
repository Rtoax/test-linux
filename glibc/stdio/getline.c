#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <setjmp.h>
#include <errno.h>
#include <string.h>

static volatile sig_atomic_t stop = 0;
static sigjmp_buf jmp;

void sig_handler(int sig)
{
	fprintf(stderr, "get sig...\n");
	stop = 1;
	siglongjmp(jmp, 1);
}

int main(int argc, char *argv[])
{
	int i, nosignal = false;
	char *buf = NULL;
	size_t buflen, n;

	for (i = 1; i < argc; i++)
		if (!strcmp(argv[i], "nosig") || !strcmp(argv[i], "nosignal")) {
			fprintf(stderr, "Running without signal!!\n");
			nosignal = true;
		}

	if (nosignal)
		goto start;

	signal(SIGINT, sig_handler);
	sigsetjmp(jmp, 1);

	if (stop) {
		if (buf)
			free(buf);
		goto goodbye;
	}

start:
	fprintf(stderr, "Usage: %s [nosig|nosignal]\n", argv[0]);
	fprintf(stderr, "Start loop!!\n");

	/**
	 * If signal(2) does not process the signal, the process will exit
	 * directly from the loop, and the return code will not be executed.
	 *
	 * Except setjmp(), we could use
	 *
	 *   poll({getlinefd, signalfd(SIGUSR1)}, ...)
	 *
	 * to handle the infinite-loop exit problem.
	 */
#if defined(TEST_getdelim)
#pragma message "Test getdelim"
	while ((n = getdelim(&buf, &buflen, '\n', stdin) >= 0) || errno == EAGAIN) {
#else
	while ((n = getline(&buf, &buflen, stdin) >= 0) || errno == EAGAIN) {
#endif
		printf("%s", buf);
	}

goodbye:
	fprintf(stderr, "Goodbye!!\n");
	return 0;
}
