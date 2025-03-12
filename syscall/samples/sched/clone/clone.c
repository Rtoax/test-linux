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

int child_fn(void *arg)
{
	int ret;

	sethostname("myhost", 6);
	/* TODO: switch root to rootfs/initramfs */
	ret = chroot("/");
	if (ret) {
		perror("chroot");
		return 0;
	}
	ret = chdir("/");
	if (ret) {
		perror("chdir");
		return 0;
	}
	ret = mount("proc", "/proc", "proc", MS_PRIVATE, NULL);
	if (ret) {
		perror("mount");
		return 0;
	}
	execlp("/bin/sh", "/bin/sh", NULL);
	printf("Ooops\n");
	return 1;
}

int main(void)
{
	int flags, status;
	pid_t pid;

	flags = CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWNS | SIGCHLD;

#if defined(PARENT_TID)
	pid_t parent_tid, child_tid;
	pid = clone(child_fn, stack + STACK_SIZE, flags, NULL,
		    &parent_tid, NULL, &child_tid);
#else
	pid = clone(child_fn, stack + STACK_SIZE, flags, NULL);
#endif
	if (pid == -1) {
		perror("clone");
		return -1;
	}

	waitpid(pid, &status, 0);
#if defined(PARENT_TID)
	printf("parent_tid = %d, child_tid = %d\n", parent_tid, child_tid);
#endif
	printf("Child exit %d.\n", status);
	return 0;
}
