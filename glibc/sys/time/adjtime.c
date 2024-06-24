#include <sys/time.h>
#include <stdio.h>

int main(void)
{
	struct timeval tv, tv2;
	struct timezone tz;

	printf("%d\n", gettimeofday(&tv, &tz));

	printf("tv_sec = %ld\n", tv.tv_sec);
	printf("tv_usec = %ld\n", tv.tv_usec);

	printf("tz_minuteswest = %d\n", tz.tz_minuteswest);
	printf("tz_dsttime = %d\n", tz.tz_dsttime);

	printf("%d\n", adjtime(&tv, &tv2));

	return 0;
}
