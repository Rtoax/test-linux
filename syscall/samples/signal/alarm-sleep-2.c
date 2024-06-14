#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>


void catch_fun(int signo)
{
	/* no need to do anything */
}

unsigned int my_sleep(unsigned int seconds)
{
	int ret = 0;
	sigset_t newset, oldset, susset;
	struct sigaction act, oldact;

	sigemptyset(&newset);
	sigaddset(&newset, SIGALRM);

	act.sa_handler = catch_fun;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	ret = sigaction(SIGALRM, &act, &oldact);
	if (ret == -1) {
		perror("sigaction\n");
		exit(1);
	}
	/* 信号屏蔽字 */
	sigprocmask(SIG_BLOCK, &newset, &oldset);

	/* 利用 sigsuspend 函数和 alarm 函数实现sleep功能 */
	alarm(seconds);

	susset = oldset;
	sigprocmask(SIG_UNBLOCK, &susset, NULL);

	/* 利用 sigsuspend 函数使进程挂起等待 */
	sigsuspend(&susset);

	/* 将时钟清0 返回值为上一次时钟剩余秒数 */
	int old = alarm(0);
	/* 恢复SIGALRM函数原来的处理方式 */
	sigaction(SIGALRM, &oldact, NULL);

	/* 解除对SIGALRM信号的屏蔽 */
	sigprocmask(SIG_SETMASK, &oldset, NULL);

	/* 返回值是上一次的剩余睡眠秒数 */
	return old;
}

int main(void)
{
	while (1) {
		printf("====mysleep 3 seconds====\n");
		my_sleep(1);
	}
	return 0;
}

