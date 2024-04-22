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
#include <linux/uio.h>
#include <elf.h>

#include "helpers.h"

size_t sigtrap_count = 0;
size_t instruction_count = 0;
sig_atomic_t keep_running = true;
bool print_ip = false;

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

void usage(char *prog)
{
	fprintf(stderr, "Usage: %s [ip]\n", prog);
}

int main(int argc, char *argv[])
{
	int i;
	pid_t child;

	signal(SIGINT, sig_handler);

	usage(argv[0]);

	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "ip"))
			print_ip = true;
	}

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
		if (print_ip)
			printf("ip = %llx\n", regs.rip);
#elif defined(__aarch64__)
		struct user_regs_struct regs;
		struct iovec regs_iov;
		regs_iov.iov_base = &regs;
		regs_iov.iov_len = sizeof(regs);
		ptrace(PTRACE_GETREGSET, child, (void *)NT_PRSTATUS, (void *)&regs_iov);
		if (print_ip)
			printf("pc = %llx\n", regs.pc);
#endif

		if (instruction_count < 5000)
			ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
		else {
			ptrace(PTRACE_CONT, child, NULL, NULL);
			break;
		}
	}

	print_count();

	/* Give child some time to print, then kill it. */
	sleep(2);
	kill(child, SIGINT);

	return 0;
}
