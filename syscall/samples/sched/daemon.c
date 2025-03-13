#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <syslog.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


/**
 * daemon(3) implementation for systems lacking one.
 */
void daemonize(int nochdir, int noclose)
{
	int fd;

	/*
	 * Ignore any possible SIGHUP when the parent process exits.
	 * Note that the iperf3 server process will eventually install
	 * its own signal handler for SIGHUP, so we can be a little
	 * sloppy about not restoring the prior value.  This does not
	 * generalize.
	 */
	signal(SIGHUP, SIG_IGN);

	/**
	 * parent exits, fork() twice to detach the child from the original
	 * parent.
	 */
	if (fork() != 0)
		exit(0);

	/* create a new session */
	setsid();

	while(1) {
		printf("[daemon:%d] is running.\n", getpid());
		sleep(1);
	}

	if (!nochdir)
		chdir("/");

	if (!noclose && (fd = open("/dev/null", O_RDWR, 0)) != -1) {
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		if (fd > STDERR_FILENO)
			close(fd);
	}
}

int main(void)
{
	daemonize(1, 1);

	/**
	 * This will not be printed.
	 */
	while (1) {
		printf("[%d] is running.\n", getpid());
		sleep(1);
	}
	return 0;
}

