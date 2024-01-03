// 什么时候会发送 SIGHUP信号？
// 当一个进程组成为孤儿进程组时，posix.1 要求 向孤儿进程组中处于停止状态的进程发送 SIGHUP（挂起）信号，
// 系统对于这种信号的默认处理是终止进程，然而如果无视这个信号或者另行处理的话，那么这个挂起进程仍可以继续执行。
//
// 子进程中注册 SIGHUP 信号处理函数，给自己发送 SIGTSTP 信号，让自己变为停止状态。
// 父进程在打印完后休眠5s，然后退出，从而导致fork出的子进程变为“孤儿进程组”中处于停止状态的进程，
// 从而导致收到 SIGHUP 信号。由于我们在子进程中注册了 SIGHUP 信号的处理函数，从而避免了子进程直接退出终止，
// 还是会再执行打印函数后再退出。
// 当将 signal(SIGHUP, signal_handle); 屏蔽后，会导致子进程在处于停止状态后直接终止退出，不会再继续执行子进程中的打印函数
//
// 这里需要注意的是 SIGTSTP 和 SIGSTOP 信号的区别：
//（1）SIGTSTP 和 SIGSTOP 信号都是使进程暂停（都可以使用 SIGCONT 信号让进程重新激活）
//（2）SIGSTOP 信号不可以被捕获，SIGTSTP 信号可以被捕获
//
// http://blog.csdn.net/zhangfangew/article/details/27070491
// http://blog.csdn.net/shandianling/article/details/17032607
// http://blog.chinaunix.net/uid-16813896-id-4992830.html

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

void signal_handle(int signum)
{
	psignal(signum, "SIG");
}

int main(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0) {
		printf("fork error\n");
	} else if (pid > 0) {
		printf("parent, pid is %d\n", getpid());
		sleep(1);
		exit(0);
	} else {
		printf("child, pid is %d\n", getpid());
		signal(SIGHUP, signal_handle);
		/* send SIGTSTP to self */
		kill(getpid(), SIGTSTP);
		printf("child\n");
		exit(0);
	}

	return 0;
}
