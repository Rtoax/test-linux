/**
 * gcov LD_PRELOAD
 *
 * gcc -shared -fpic gcov_preload.c -o libgcov_preload.so
 * LD_PRELOAD=./libgcov_preload.so ./test.out
 *
 * https://blog.csdn.net/yanxiangyfg/article/details/80989680
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <signal.h>
#define SIMPLE_WAY

void sighandler(int signo)
{
#ifdef SIMPLE_WAY
	exit(signo);
#else
	extern void __gcov_flush();
	__gcov_flush(); /* flush out gcov stats data */
	raise(signo); /* raise the signal again to crash process */
#endif
}

/**
 * 用来预加载的动态库gcov_preload.so的代码如下
 * 其中__attribute__ ((constructor))是gcc的符号，它修饰的函数会在main函数
 * 执行之前调用，我们利用它把异常信号拦截到我们自己的函数中，然后调用
 * __gcov_flush()输出错误信息。
 *
 * 设置预加载库 LD_PRELOAD=./gcov_preload.so
 */
__attribute__ ((constructor))
void ctor()
{
	int sigs[] = {
		SIGILL, SIGFPE, SIGABRT, SIGBUS,
		SIGSEGV, SIGHUP, SIGINT, SIGQUIT,
		SIGTERM
	};
	int i;
	struct sigaction sa;
	sa.sa_handler = sighandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESETHAND;

	for (i = 0; i < sizeof(sigs)/sizeof(sigs[0]); ++i) {
		if (sigaction(sigs[i], &sa, NULL) == -1) {
			perror("Could not set signal handler");
		}
	}
}
