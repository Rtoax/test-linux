#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <syslog.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


#define MAXFD 64

int my_daemon(void)
{
	int i;
	pid_t pid;

	if ((pid = fork()) != 0) {
		printf("parent terminates.\n");
		exit(0);
	}

	setsid();
	perror("setsid: ");

	signal(SIGHUP, SIG_IGN);

	if ((pid=fork()) != 0) {
		printf("1st child terminates.\n");
		exit(0);
	}

	chdir("/home/rongtao");
	perror("chdir: ");
	umask(0);

	for (i = 0; i < MAXFD; i++) {
		printf("close fd = %d\n", i);
		close(i);
		perror("close: ");
	}

	openlog("openlog_name", LOG_PID, 0);
	perror("openlog: ");

	return 0;
}

int main(void)
{
	my_daemon();
	return 0;
}

