#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


int n = 0;
int flag = 0;

void sig_child(int num)
{
	printf("I'm child[%d]: n = %d\n",getpid(),n);
	n += 2;
	flag = 1;
	sleep(1);
}

void sig_parent(int num)
{
	printf("I'm parent[%d]: n = %d\n",getpid(),n);
	n += 2;
	flag = 1;
	sleep(1);
}

int main(void)
{
	struct sigaction act;
	pid_t pid;

	pid = fork();
	if (pid < 0) {
		perror("fork\n");
		exit(1);
	} else if(pid == 0) {
		n = 2;
		sigemptyset(&act.sa_mask);
		act.sa_handler = sig_child;
		act.sa_flags = 0;

		sigaction(SIGUSR1, &act, NULL);

		while (1) {
			if (flag == 1) {
				/* Send SIGUSR1 to parent */
				kill(getppid(), SIGUSR2);
				flag = 0;
			}
		}
	} else {
		n = 1;
		sleep(2);

		sigemptyset(&act.sa_mask);
		act.sa_handler = sig_parent;
		act.sa_flags = 0;

		sigaction(SIGUSR2, &act, NULL);

		sig_parent(0);
		while (1) {
			if (flag == 1) {
				/* Send SIGUSR1 to child */
				kill(pid, SIGUSR1);
				flag = 0;
			}
		}
	}

	return 0;
}

