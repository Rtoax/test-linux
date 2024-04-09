#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

char *get_timestamp(void)
{
	time_t now = time(NULL);
	return asctime(localtime(&now));
}

int main(int argc, char* argv[])
{
	printf("%s", get_timestamp());
	return 0;
}
