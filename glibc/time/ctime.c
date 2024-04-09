#include <time.h>
#include <stdio.h>
#include <malloc.h>


int main(void)
{
	time_t t = 12;
	char *str1;
	char *str2;
	char buf[26];

	str1 = ctime(&t);
	printf("%s\n", str1);

	str2 = ctime_r(&t, buf);
	printf("%s\n", str2);

	return 0;
}

