#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


void handler(int signum)
{
	printf("Get signal %s, pid %d\n", strsignal(signum), getpid());
	exit(1);
}

int main(void)
{
	int i = 0;
	pid_t pid, ppid;

	signal(SIGINT, handler);
	ppid = getpid();
	printf("Parent pid %d\n", ppid);

	/* Fork 5 children */
	for (i = 0; i < 5; i++) {
		pid = fork();
		signal(SIGINT, handler);

		if (pid == 0)
			break;
	}

	if (i < 5) {
		printf("%dth child pid %d\n", i + 1, getpid());
		/* Kill parent */
		if (i == 4)
			kill(ppid, SIGINT);
	} else {
		sleep(1);
	}

	return 0;
}
