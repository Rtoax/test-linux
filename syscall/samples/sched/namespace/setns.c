#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sched.h>
#include <syscall.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int sys_setns(int fd, int nstype)
{
	return syscall(SYS_setns, fd, nstype);
}

int main(int argc, char *argv[])
{
	int fd;
	if (argc < 3) {
		fprintf(stderr, "%s /proc/PID/ns/FILE cmd args...\n", argv[0]);
		fprintf(stderr, "$ sudo %s /proc/self/ns/ipc ls\n", argv[0]);
		return -1;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1){
		printf("error open %s\n", argv[1]);
		exit(1);
	}

	if (setns(fd, CLONE_NEWPID) == -1){
		fprintf(stderr, "setns: %m\n");
		close(fd);
		exit(1);
	}

	execvp(argv[2], &argv[2]);

	return 0;
}

