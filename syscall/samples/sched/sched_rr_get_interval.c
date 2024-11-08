/**
 * SCHED_RR 与 SCHED_FIFO 不同
 *
 * SCHED_RR 在循环循环中分配具有相同优先级的并发进程。为每个进程分配了时间片。
 * sched_rr_get_interval() 函数将报告已分配给每个进程的时间片。
 * 即使POSIX要求此功能只能与SCHED_RR进程一起使用，sched_rr_get_interval() 功能
 * 仍可以检索Linux上任何进程的时间片长度。
 *
 * 以下命令以不同的策略和优先级运行测试程序。
 * 具有SCHED_FIFO策略的进程将返回0秒和0纳秒的时间片，表明它是无限的：
 *
 * $ sudo chrt --fifo 10 ./sched_rr_get_interval
 * 0, 0
 *
 * $ sudo chrt --rr 10 ./sched_rr_get_interval
 * 0, 100000000
 *
 * $ sudo chrt --rr 1 ./sched_rr_get_interval
 * 0, 100000000
 *
 * $ sudo chrt --other 0 ./sched_rr_get_interval
 * 0, 3000000
 */
#include <sched.h>
#include <stdio.h>
#include <unistd.h>


int main(void)
{
	int ret;
	struct timespec _timespec;

	ret = sched_rr_get_interval(getpid(), &_timespec);
	if (ret == -1) {
		fprintf(stderr, "sched_rr_get_interval: %m\n");
		return 1;
	}

	printf("%ld, %ld\n", _timespec.tv_sec, _timespec.tv_nsec);

	return 0;
}
