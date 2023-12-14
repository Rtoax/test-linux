#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <elf.h>
#include <stdint.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>


uint64_t elfentry(const char *path)
{
	Elf64_Ehdr ehdr;
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return 0;
	read(fd, (void*)&ehdr, sizeof(ehdr));
	printf("ehdr.e_ident = %s\n", ehdr.e_ident);
	printf("ehdr.e_entry = 0x%lx\n", ehdr.e_entry);
	close(fd);
	return ehdr.e_entry;
}

int main(int argc, char *argv[])
{
	pid_t child;
	int status;
	char byte1 = 'a';

	uint64_t addr = elfentry("/bin/ls");

	child = fork();
	if (child == 0) {
		/* 本进程将被父进程跟踪，其父进程应该希望跟踪子进程 */
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execl("/bin/ls", "/bin/ls", NULL);
		exit(0);
	} else {
		/* 接收被子进程发送过来的 SIGCHLD 信号 */
		wait(&status);

		/* 如果子进程退出了, 那么终止跟踪 */
		if (WIFEXITED(status)) {
			return 0;
		}
		/**
		 * 从内存地址代码段中读取一个字节，内存地址由 addr 给出
		 */
		ptrace(PTRACE_PEEKTEXT, child, (void*)addr, &byte1);
		perror("ptrace: ");
		printf("PTRACE_PEEKTEXT <%c>\n", byte1);
	}

	return 0;
}

