#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#if defined(__x86_64__)
#include <sys/reg.h>
#endif
#include <sys/user.h>
#include <sys/syscall.h>
#include <sys/ptrace.h>

#include "helpers.h"


size_t sigtrap_count = 0;
size_t instruction_count = 0;

void print_count(void)
{
	printf("instruction count %ld\n", instruction_count);
	printf("SIGTRAP count %ld\n", sigtrap_count);
}

void sig_handler(int signo)
{
	print_count();
	exit(1);
}

int main(void)
{
	pid_t child;

	signal(SIGINT, sig_handler);

	child = fork();
	if (child == 0) {
		execl("./pthread_create", "./pthread_create", NULL);
	}

	/* Child need some time to load and run */
	sleep(1);

	/* Parent process */
	ptrace(PTRACE_ATTACH, child, NULL, NULL);

	while (1) {
		int status;
		waitpid(child, &status, 0);
		if (WIFEXITED(status)) {
			printf("exit.\n");
			break;
		}
		if (WSTOPSIG(status) == SIGTRAP)
			sigtrap_count++;
		instruction_count++;
		usleep(2000);

		ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
	}

	print_count();

	return 0;
}

