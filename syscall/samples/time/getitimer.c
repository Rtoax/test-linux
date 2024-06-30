#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>


void printmsg(int sig)
{
	printf("Hello world\n");
	return ;
}
int main(void)
{
	struct itimerval curr_value;
	int ret ;
	struct itimerval tick;

	signal(SIGALRM, printmsg);

	tick.it_value.tv_sec = 1; //1s 后启动定时器
	tick.it_value.tv_usec = 2;

	tick.it_interval.tv_sec = 1; //定时器启动后，每个一秒执行响应函数
	tick.it_interval.tv_usec = 4;

	ret = setitimer(ITIMER_REAL, &tick, NULL);
	printf("ret = %d-----------\n", ret);

	ret = getitimer(ITIMER_REAL, &curr_value);
	printf("ret = %d-----------\n", ret);
	printf("it_interval.tv_sec  = %ld\n", curr_value.it_interval.tv_sec);
	printf("it_interval.tv_usec = %ld\n", curr_value.it_interval.tv_usec);
	printf("it_value.tv_sec = %ld\n", curr_value.it_value.tv_sec);
	printf("it_value.tv_usec = %ld\n", curr_value.it_value.tv_usec);

	ret = getitimer(ITIMER_VIRTUAL, &curr_value);
	printf("ret = %d-----------\n", ret);
	printf("it_interval.tv_sec  = %ld\n", curr_value.it_interval.tv_sec);
	printf("it_interval.tv_usec = %ld\n", curr_value.it_interval.tv_usec);
	printf("it_value.tv_sec = %ld\n", curr_value.it_value.tv_sec);
	printf("it_value.tv_usec = %ld\n", curr_value.it_value.tv_usec);

	ret = getitimer(ITIMER_PROF, &curr_value);
	printf("ret = %d-----------\n", ret);
	printf("it_interval.tv_sec  = %ld\n", curr_value.it_interval.tv_sec);
	printf("it_interval.tv_usec = %ld\n", curr_value.it_interval.tv_usec);
	printf("it_value.tv_sec = %ld\n", curr_value.it_value.tv_sec);
	printf("it_value.tv_use = %ld\n", curr_value.it_value.tv_usec);

	printf("Wait. getchar\n");
	getchar();
	return 0;
}
