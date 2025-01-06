#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>

#define err_exit(en, msg) do {	\
		errno = en;	\
		perror(msg);	\
		exit(EXIT_FAILURE);	\
	} while (0);

void child_sig_handler(int sig)
{
	psignal(sig, "---");
}

static void *sig_thread(void *arg)
{
	sigset_t *set = (sigset_t *)arg;
	int s, sig;

	signal(SIGUSR1, child_sig_handler);

	for (;;) {
		/* Waiting signal. */
		s = sigwait(set, &sig);
		if (s != 0)
			err_exit(s, "sigwait");

		printf("signal handling thread got signal %d\n", sig);
		if (sig == SIGINT)
			return NULL;
	}

	return NULL;
}

int main(int argc, const char *argv[])
{
	pthread_t thread;
	sigset_t set;
	int s;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);

	/* mask signals */
	s = pthread_sigmask(SIG_BLOCK, &set, NULL);
	if (s != 0)
		err_exit(s, "pthread_sigmask");

	s = pthread_create(&thread, NULL, &sig_thread, (void *)&set);
	if (s != 0)
		err_exit(s, "pthread_create");

	sleep(1);

	printf("Send SIGUSR1 to thread.\n");
	pthread_kill(thread, SIGUSR1);

	pthread_join(thread, NULL);

	return 0;
}
