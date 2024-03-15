#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	printf("pid  = %d\n", getpid());
	printf("ppid = %d\n", getppid());
	printf("pgid = %d\n", getpgid(0));
	printf("pgrp = %d\n", getpgrp());

	return 0;
}
