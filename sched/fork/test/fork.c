/**
 * File: fork.c
 * Author: Rong Tao
 * Date: 2022.05.10
 */
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int pid;

	if ((pid = fork()) == 0) {
		printf("Child %d.\n", getpid());
	} else if (pid > 0) {
		printf("Parent %d.\n", getpid());
		waitpid(pid, NULL, 0);
	}
	return 0;
}
