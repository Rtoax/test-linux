#include <stdio.h>
#include <time.h>
#include <malloc.h>

int main(void)
{
	time_t time = 0;
	struct tm *t2, tbuf;
	t2 = localtime_r(&time, &tbuf);

	char *s1 = asctime(t2);
	printf("%s\n", s1);

	char buf[32];
	char *s2 = asctime_r(t2, buf);
	printf("%s\n", s2);
	return 0;
}
