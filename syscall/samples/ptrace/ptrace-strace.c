#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#if defined(__x86_64__)
#include <sys/reg.h>
#endif
#include <sys/user.h>
#include <sys/syscall.h>
#include <sys/ptrace.h>
#include <sys/uio.h>

#include "ptrace_helpers.h"

#ifndef NT_PRSTATUS
#define NT_PRSTATUS 1
#endif

int main(void)
{
	pid_t child;
	int status;
	int iscalling = 0;
#if defined(__aarch64__) || defined(__x86_64__)
	struct user_regs_struct regs;
#elif defined(__sw_64__)
	struct user regs;
#endif

	child = fork();
	if (child == 0) {
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execl("/bin/ls", "ls", "-l", "-h", NULL);
	}

	(void)iscalling;

	/* Parent process */
	while (1) {
		wait(&status);
		/**
		 * 检查子进程是暂停还准备退出
		 */
		if (WIFEXITED(status))
			break;
#if defined(__aarch64__) || defined(__sw_64__)
		struct iovec regs_iov;
		regs_iov.iov_base = &regs;
		regs_iov.iov_len = sizeof(regs);

		ptrace(PTRACE_GETREGSET, child, (void *)NT_PRSTATUS,
			(void *)&regs_iov);

# if defined(__aarch64__)
		printf("Call syscall %lld, \033[31m%s\033[m\n", regs.regs[8],
		       find_syscall_symbol(regs.regs[8]));
# elif defined(__sw_64__)
		printf("Call syscall %ld, \033[31m%s\033[m\n", regs.regs[12],
		       find_syscall_symbol(regs.regs[12]));
# endif
#elif defined(__x86_64__)
		long orig_rax;

		orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX, NULL);

		printf("Call syscall %ld, \033[31m%s\033[m\n", orig_rax,
		       find_syscall_symbol(orig_rax));

		if (orig_rax == SYS_write) {
			ptrace(PTRACE_GETREGS, child, NULL, &regs);
			if (!iscalling) {
				iscalling = 1;
				printf("SYS_write call with %lld, %lld, %lld\n",
				       regs.rdi, regs.rsi, regs.rdx);
			} else {
				printf("SYS_write call return %lld\n",
				       regs.rax);
				iscalling = 0;
			}
		}
#endif
		/**
		 * 使暂停的子进程继续执行，并在子进程下次进行系统调用前或系统调
		 * 后，向子进程发送 SINTRAP 信号量，让子进程暂停。
		 */
		ptrace(PTRACE_SYSCALL, child, NULL, NULL);
	}
	return 0;
}
