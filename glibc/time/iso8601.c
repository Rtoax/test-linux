#include <time.h>
#include <stdio.h>
#include <string.h>


char *iso8601(char local_time[32])
{
	time_t t_time;
	struct tm *t_tm;

	t_time = time(NULL);
	t_tm = localtime(&t_time);
	if (t_tm == NULL)
		return NULL;

	if(strftime(local_time, 32, "%FT%T%z", t_tm) == 0)
		return NULL;

	local_time[25] = local_time[24];
	local_time[24] = local_time[23];
	local_time[22] = ':';
	local_time[26] = '\0';

	return local_time;
}

int main(void)
{
	char buf[32] = {0};
	printf("ISO Time: %s\n", iso8601(buf));
	return 0;
}
