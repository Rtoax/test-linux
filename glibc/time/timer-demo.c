#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>


void sigev_notify_fn(union sigval sv)
{
	timer_t *ptimerid = (timer_t *)sv.sival_ptr;
	int cnt = timer_getoverrun(*ptimerid);
	printf("CB: %p, %d\n", *ptimerid, cnt);
}

int main(void)
{
	timer_t timerid;
	struct sigevent sev;
	int ret;

	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_value.sival_ptr = &timerid;

	sev.sigev_notify_function = sigev_notify_fn;
	sev.sigev_notify_attributes = NULL;

	timer_create(CLOCK_REALTIME, &sev, &timerid);

	printf("timer_create: timerid  = %p\n", timerid);

	struct timespec tp;
	clock_gettime(CLOCK_REALTIME, &tp);

	struct itimerspec newit;

	newit.it_value.tv_sec = tp.tv_sec + 1;
	newit.it_value.tv_nsec = tp.tv_nsec;
	newit.it_interval.tv_sec = 1;
	newit.it_interval.tv_nsec = 0;

	ret = timer_settime(timerid, TIMER_ABSTIME, &newit, NULL);
	if (ret < 0) {
		perror("timer_settime:");
	}

	printf("timer_settime: val(%ld,%ld), inte(%ld,%ld)\n",
		newit.it_value.tv_sec, newit.it_value.tv_nsec,
		newit.it_interval.tv_sec, newit.it_interval.tv_nsec);

	while (1)
		sleep(1);

	timer_delete(timerid);

	return 0;
}

