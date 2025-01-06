#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>


void catch_fun(int signo)
{
	printf("--------sigaction--------\n");
	sleep(1);
}

int main(void)
{
	int ret;
	sigset_t set;
	struct sigaction act;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGTSTP);

	act.sa_handler = catch_fun;
	act.sa_mask = set;
	act.sa_flags = 0;

	ret = sigaction(SIGTSTP, &act, NULL);
	if (ret == -1) {
		perror("sigaction\n");
		exit(1);
	}

	while (1)
		sleep(1);

	return 0;
}
