#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "time_helpers.h"


char *get_timestamp(void)
{
	time_t now = time(NULL);
	return asctime(localtime(&now));
}

int main(int argc, char* argv[])
{
	time_t time = 1;
	struct tm *t, *t2, rslt;

	t = localtime(&time);
	t2 = localtime_r(&time, &rslt);

	print_tm(t);
	print_tm(t2);

	printf("%s", get_timestamp());

	return 0;
}
