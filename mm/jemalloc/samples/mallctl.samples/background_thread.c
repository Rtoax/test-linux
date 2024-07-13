#include <stdio.h>
#include <jemalloc/jemalloc.h>

//Enable/disable internal background worker threads. When set to true, background threads are created on demand (the
//number of background threads will be no more than the number of CPUs or active arenas). Threads run periodically, and
//handle purging asynchronously. When switching off, background threads are terminated synchronously. Note that after
//fork(2) function, the state in the child process will be disabled regardless the state in parent process. See stats.
//background_thread for related stats. opt.background_thread can be used to set the default option. This option is only
//available on selected pthread-based platforms.
//enable或者disable内部后台工作线程。当enable时，后台线程要求创建（后台线程不比CPU数或者arenas数量多）。
//线程将周期执行，并且异步地处理清理。当关闭，后台线程同步终止。
//fork函数之后，子进程的状态将忽略父进程的状态。（see stats）
//background_thread相关的状态。 opt.background_thread
//可以设置默认选项。这个选项仅仅在基于pthread的系统中生效。


void set_jemalloc_bg_thread(bool enable) {
	/* let jemalloc do purging asynchronously, required when there's no traffic
	 * after flushdb */
	char val = !!enable;
	je_mallctl("background_thread", NULL, 0, &val, 1);
}
void get_jemalloc_bg_thread(bool *enable) {
	/* let jemalloc do purging asynchronously, required when there's no traffic
	 * after flushdb */
	size_t size = sizeof(bool);
	je_mallctl("background_thread", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	set_jemalloc_bg_thread(enable);

	enable = false;
	get_jemalloc_bg_thread(&enable);
	printf("enable = %d\n", enable);
}
