/**
 * SIGHUP
 *
 * Q: When is the SIGHUP signal sent?
 *
 * - When a process group becomes an orphan(孤儿) process group, POSIX.1
 *   requires that a SIGHUP (hangup) signal be sent to the stopped process
 *   in the orphan process group. The system's default processing for this
 *   signal is to terminate the process. However, if this signal is ignored
 *   or processed separately, the suspended process can continue to execute.
 *
 * - SIGHUP sent to a process when its controlling terminal is closed.
 *
 * Refs:
 * https://en.wikipedia.org/wiki/SIGHUP
 * http://blog.csdn.net/zhangfangew/article/details/27070491
 * http://blog.csdn.net/shandianling/article/details/17032607
 * http://blog.chinaunix.net/uid-16813896-id-4992830.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

#include "../wait/waitpid-status.c"

void sig_printer(int signum)
{
	psignal(signum, "SIG");
}

int main(void)
{
	int ret;
	pid_t pid;
	int status = 0;

	pid = fork();
	if (pid < 0) {
		printf("fork error\n");
	}

	/* Child */
	if (pid == 0) {
		int i;

		printf("child, pid is %d\n", getpid());
		signal(SIGHUP, sig_printer);

		for (i = 0; i < 2; i++) {
			printf("Child running...\n");
			usleep(100000);
		}

		/* send SIGTSTP to self, make self stop */
		kill(getpid(), SIGTSTP);
		printf("child\n");

		exit(0);
	}

	/* Parent */
	printf("parent, pid is %d\n", getpid());
	sleep(1);
	ret = waitpid(pid, &status, WNOHANG);
	print_wstatus(status);
	printf("Parent exit, waitpid %d status %d.\n", ret, status);
	exit(0);

	return 0;
}
