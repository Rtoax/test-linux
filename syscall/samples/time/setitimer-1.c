#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include<signal.h>

void catch_fun(int signo)
{
    printf("catch signal\n");
}

int main(void)
{
    int ret;
    struct itimerval sa;

    sa.it_value.tv_sec = 5;
    sa.it_value.tv_usec = 0;
    sa.it_interval.tv_sec = 3;
    sa.it_interval.tv_usec = 0;

    signal(SIGALRM, catch_fun);

    ret = setitimer(ITIMER_REAL, &sa, NULL);
    if (-1 == ret) {
        perror("setitimer\n");
        exit(1);
    }

    while (1);

    return 0;

}
