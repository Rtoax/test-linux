#define __USE_GNU /* TIMEVAL_TO_TIMESPEC */
#include <stdio.h>
#include <sys/time.h>

int main(void)
{
	struct timeval tv1 = {0, 0}, tv2;
	struct timespec ts1 = {0, 0};

	tv1.tv_sec = 12;
	tv1.tv_usec = 23;

#ifdef __USE_GNU
	TIMEVAL_TO_TIMESPEC(&tv1, &ts1);
	TIMESPEC_TO_TIMEVAL(&tv2, &ts1);
#endif
	printf("timespec: %ld, %ld\n", ts1.tv_sec, ts1.tv_nsec);
	printf("timespec: %ld, %ld\n", tv2.tv_sec, tv2.tv_usec);

	return 0;
}
