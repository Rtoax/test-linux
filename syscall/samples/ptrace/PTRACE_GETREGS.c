#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <elf.h>
#include <stdint.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>

#include "helpers.h"


int main(int argc, char *argv[])
{
	pid_t child;
	int status;
	struct user_regs_struct regs;


	child = fork();
	if (child == 0) {
		/* 本进程将被父进程跟踪，其父进程应该希望跟踪子进程 */
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execl("/bin/ls", "/bin/ls", NULL);
		exit(0);
	} else {
		/* 接收子进程发送的 SIGCHLD 信号 */
		wait(&status);
		/* 如果子进程退出了, 那么终止跟踪 */
		if (WIFEXITED(status))
			return 1;

		/* 获取被跟踪进程寄存器的值 */
		ptrace(PTRACE_GETREGS, child, 0, &regs);
		perror("ptrace: ");

		print_user_regs_struct(&regs);
	}

	return 0;
}
