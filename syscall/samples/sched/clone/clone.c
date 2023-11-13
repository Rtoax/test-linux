#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>


#define STACK_SIZE (1024 * 1024)

static char stack[STACK_SIZE];

int child(void* arg)
{
	int ret;

	sethostname("myhost", 6);
	/* TODO: switch root to rootfs/initramfs */
	ret = chroot("/");
	if (ret) {
		perror("chroot");
		return 0;
	}
	chdir("/");
	mount("proc", "/proc", "proc", 0, NULL);
	execlp("/bin/sh", "/bin/sh" , NULL);
	printf("Ooops\n");
	return 1;
}

int main(void)
{
	int flags;
	pid_t pid;

	flags = CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWNS | SIGCHLD;
	pid = clone(child, stack + STACK_SIZE, flags, NULL);
	if (pid == -1) {
		perror("clone");
		return -1;
	}

	waitpid(pid, NULL, 0);
	return 0;
}

