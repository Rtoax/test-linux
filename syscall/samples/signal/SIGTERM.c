/**
 * SIGTERM
 *
 * The default action for a process receiving SIGTERM is to terminate.
 * Processes can handle SIGTERM by defining a signal handler. This allows the
 * process to perform cleanup tasks, such as closing files or releasing
 * resources, before exiting.
 *
 * Generate conditions:
 * - kill -TERM PID.
 * - Terminator exit.
 * - System shutdown, halt, reboot.
 * - docker/podman stop.
 * - systemctl stop.
 */
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


void sig_handler(int signum)
{
	fprintf(stderr, "pid %d get %s\n", getpid(), strsignal(signum));
	exit(1);
}

int main(void)
{
	pid_t pid;

	signal(SIGTERM, sig_handler);

	pid = fork();
	if (pid == 0) {
		printf("child %d\n", getpid());
		sleep(100);
	}

	sleep(1);
	printf("parent %d kill %d\n", getpid(), pid);
	kill(pid, SIGTERM);

	return 0;
}
