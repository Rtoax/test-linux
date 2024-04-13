#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define err_sys(fmt, arg...) \
	do { \
		printf(fmt, ##arg);\
		printf("\nerrno: %d %s\n", errno, strerror(errno));\
		exit(EXIT_FAILURE);\
	} while (0)

/**
 * 关于 open 函数 O_CLOEXEC 模式，fcntl 函数 FD_CLOEXEC 选项，总结为如下几点：
 *
 * 1. 调用 open 函数 O_CLOEXEC 模式打开的文件描述符在执行 exec 调用新程序中关闭，
 *    且为原子操作。
 * 2. 调用 open 函数不使用 O_CLOEXEC 模式打开的文件描述符，然后调用 fcntl 函数
 *    设置 FD_CLOEXEC 选项，效果和使用 O_CLOEXEC 选项 open 函数相同，但分别调用
 *    open、fcnt两个函数，不是原子操作，多线程环境中存在竞态条件，故用 open 函
 *    数 O_CLOEXEC 选项代替之。
 * 3. 调用 open 函数 O_CLOEXEC 模式打开的文件描述符，或是使用 fcntl 设置
 *    FD_CLOEXEC 选项，这二者得到的描述符在通过 fork 调用产生的子进程中均不被关闭。
 * 4. 调用dup族类函数得到的新文件描述符将清除O_CLOEXEC模式。
 */

int main(void)
{
	int fd;
#ifdef _O_CLOEXEC
	if ((fd = open("my.txt", O_RDWR | O_CREAT | O_CLOEXEC, 0600)) < 0)
#else
	if ((fd = open("my.txt", O_RDWR | O_CREAT, 0600)) < 0)
#endif
		err_sys("open error");

#ifdef _DUP
	int fd2;
	if ((fd2 = dup(fd)) < 0)
		err_sys("dup error");
	if (write(fd2, "123", 3) < 0)
		err_sys("write error");
#endif

#ifdef _FCNTL_CLOEXEC
	int val;
	if ((val = fcntl(fd, F_GETFD)) < 0)
		err_sys("fcntl(F_GETFD) error");

	val |= FD_CLOEXEC;
	if (fcntl(fd, F_SETFD, val) < 0)
		err_sys("fcntl( F_SETFD) error");
#endif

#ifndef _FORK
	if (execl("/bin/sleep", "sleep", "10000", (void*)0) < 0)
		err_sys("execl error");
#else
	pid_t pid;
	switch ((pid = fork())) {
	case -1:
		err_sys("fork error");
	case 0:
		sleep(10000);
		break;
	default:
		sleep(10000);
		break;
	}
#endif
	return 0;
}

