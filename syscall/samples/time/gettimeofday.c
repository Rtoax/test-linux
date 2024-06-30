#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>


void test1(void)
{
	char buffer[40];
	struct timeval time;

	gettimeofday(&time, NULL);
	sleep(1);

	strftime(buffer, 40, "Current date/time: %m-%d-%Y/%T", localtime(&time.tv_sec));
	printf("%s\n",buffer);
}

void test2_print_time(void)
{
	struct timeval tv;
	struct tm* ptm;
	char time_string[40];
	long milliseconds;
	/* Obtain the time of day, and convert it to a tm struct. */
	gettimeofday(&tv, NULL);
	ptm = localtime(&tv.tv_sec);
	/* Format the date and time, down to a single second. */
	strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", ptm);
	/* Compute milliseconds from microseconds. */
	milliseconds = tv.tv_usec / 1000;
	/* Print the formatted time, in seconds, followed by a decimal point
	 * and the milliseconds. */
	printf("%s.%03ld\n", time_string, milliseconds);
}

void test3(void)
{
	struct timeval tv;
	struct timezone tz;

	printf("%d\n", gettimeofday(&tv, &tz));

	printf("tv_sec = %ld\n", tv.tv_sec);
	printf("tv_usec = %ld\n", tv.tv_usec);
	printf("tz_minuteswest = %d\n", tz.tz_minuteswest);
	printf("tz_dsttime = %d\n", tz.tz_dsttime);
}

int main(int argc, char **argv)
{
	test1();
	test2_print_time();
	test3();
	return 0;
}
