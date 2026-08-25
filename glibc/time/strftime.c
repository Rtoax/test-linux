#include <stdio.h>
#include <time.h>
#include <sys/time.h>

void test_1(void)
{
	time_t t = time(NULL);
	struct tm t2, *pt2;
	char str[256];

	pt2 = localtime_r(&t, &t2);

#define T(fmt)                                      \
	do {                                        \
		strftime(str, 1024, fmt, pt2);      \
		printf("%s = \"%s\"\n", #fmt, str); \
	} while (0)

	T("%A");
	T("%a");
	T("%B");
	T("%b");
	T("%C");
	T("%c");
	T("%D");
	T("%d");
	//T("%E");
	T("%e");
	T("%F");
	T("%G");
	T("%g");
	T("%G");
	T("%H");
	T("%h");
	T("%I");
	T("%j");
	T("%k");
	T("%l");
	T("%m");
	T("%M");
	T("%n");
	//T("%O");
	T("%P");
	T("%p");
	T("%R");
	T("%r");
	T("%s");
	T("%T");
	T("%u");
	T("%U");
	T("%V");
	T("%w");
	T("%W");
	T("%x");
	T("%X");
	T("%Y");
	T("%y");
	T("%z");
	T("%Z");
	T("%Z");
	//T("%+");
	T("%%");
#undef T
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
