#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
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
sig_atomic_t keep_running = true;

void print_count(void)
{
	printf("instruction count %ld\n", instruction_count);
	printf("SIGTRAP count %ld\n", sigtrap_count);
}

void sig_handler(int signo)
{
	print_count();
	keep_running = false;
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

	while (keep_running) {
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

#if defined(__x86_64__)
		struct user_regs_struct regs;
		ptrace(PTRACE_GETREGS, child, NULL, &regs);
		printf("ip = %llx\n", regs.rip);
#endif

		ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
	}

	print_count();

	return 0;
}
