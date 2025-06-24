#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

/* FIXME: In some glibc, there is no gettid() */
int sys_gettid(void)
{
	return syscall(__NR_gettid);
}
#define gettid() sys_gettid()

/* Returns the process ID of the calling processes, as determined from
 * the /proc/self symlink. */
pid_t get_pid_from_proc_self(void)
{
	char target[32];
	int pid;
	readlink("/proc/self", target, sizeof(target));
	sscanf(target, "%d", &pid);
	return (pid_t)pid;
}

pid_t get_tid_from_proc_thread_self(void)
{
	char target[64];
	int tid;
	readlink("/proc/thread-self", target, sizeof(target));
	sscanf(target, "%d", &tid);
	return (pid_t)tid;
}

int main(void)
{
	printf("/proc/self reports process id %d\n", get_pid_from_proc_self());
	printf("getpid() reports process id %d\n", getpid());
	printf("/proc/thread-self reports thread id %d\n", get_tid_from_proc_thread_self());
	printf("gettid() reports thread id %d\n", gettid());
	return 0;
}
