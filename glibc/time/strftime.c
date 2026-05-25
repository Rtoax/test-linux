#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int test_1(void)
{
	time_t t = time(NULL);
	struct tm t2, *pt2;
	pt2 = localtime_r(&t, &t2);

	char str[1024];
	strftime(str, 1024, "%A %a %B %b %C %c %%\n", pt2);
	printf("%s\n", str);

	return 0;
}

void test_2(void)
{
	char buffer[40];
	struct timeval tv;
	gettimeofday(&tv, NULL);
	time_t t = time(NULL);

	strftime(buffer, 40, "Current date/time: %m-%d-%Y/%T",
		 localtime(&tv.tv_sec));
	printf("%s\n",buffer);
	strftime(buffer, 40, "Current date/time: %m-%d-%Y/%T", localtime(&t));
	printf("%s\n",buffer);
}

int main(void)
{
	test_1();
	test_2();
	return 0;
}
