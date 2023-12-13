#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <sys/ptrace.h>


int main(void)
{
	pid_t child;
	long orig_rax;
	int status;
	int iscalling=0;
	struct user_regs_struct regs;

	child = fork();
	if (child == 0) {
		ptrace(PTRACE_TRACEME,0,NULL,NULL);
		execl("/bin/ls","ls","-l","-h",NULL);
	}

	/* Parent process */
	while (1) {
		wait(&status);
		/**
		 * 检查子进程是暂停还准备退出
		 */
		if(WIFEXITED(status))
			break;
		orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX, NULL);
		if (orig_rax == SYS_write) {
			ptrace(PTRACE_GETREGS, child, NULL, &regs);
			if (!iscalling) {
				iscalling =1;
				printf("SYS_write call with %lld, %lld, %lld\n",
					regs.rdi, regs.rsi, regs.rdx);
			} else {
				printf("SYS_write call return %lld\n", regs.rax);
				iscalling = 0;
			}
		}
		/**
		 * 使暂停的子进程继续执行，并在子进程下次进行系统调用前或系统调
		 * 后，向子进程发送 SINTRAP 信号量，让子进程暂停。
		 */
		ptrace(PTRACE_SYSCALL, child, NULL, NULL);
	}
	return 0;
}

