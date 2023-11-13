#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];

static int child_fn(void *arg)
{
	sleep(1);
	system("ifconfig veth1 10.0.0.4");
	puts("========= child network interfaces ========");
	system("ifconfig -a");
	puts("===========================================");
	sleep(1);
	system("ping -c 3 10.0.0.3");
	return 0;
}

int main(void)
{
	char buf[255];

	pid_t pid = clone(child_fn, child_stack + STACK_SIZE, CLONE_NEWNET, NULL);
	if (pid == -1) {
		perror("clone");
		return -1;
	}

	sprintf(buf, "ip link add name veth0 type veth peer name veth1 netns %d", pid);
	system(buf);
	system("ifconfig veth0 10.0.0.3");

	waitpid(pid, NULL, 0);
	return 0;
}

