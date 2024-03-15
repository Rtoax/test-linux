#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;

	printf("pid  = %d\n", getpid());
	printf("ppid = %d\n", getppid());
	printf("pgid = %d\n", getpgid(0));
	printf("pgrp = %d\n", getpgrp());

	pid = fork();
	if (pid < 0) {
		perror("fork!\n");
		exit(1);
	}

	/* child */
	if (pid == 0) {
		printf("child: pid = %d, gid = %d \n", getpid(), getpgid(0));
		printf("child: pid = %d, gid = %d \n", getpid(), getpgrp());

		sleep(2);

		printf("child: pid = %d, gid = %d (after setpgid)\n", getpid(), getpgrp());
		exit(1);
	}

	/* parent */

	sleep(1);

	setpgid(pid, pid);

	sleep(3);

	printf("parent: pid = %d, gid = %d \n", getpid(), getpgid(0));

	sleep(1);

	setpgid(getpid(), getpid());
	printf("parent: pid = %d, gid = %d (after setpgid)\n", getpid(), getpgrp());

	setpgid(getpid(), getppid());
	printf("parent: pid = %d, gid = %d (after base ppid)\n", getpid(), getpgrp());

	waitpid(pid, NULL, 0);

	return 0;
}
