#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/* sa -  summarizes accounting information */

int main(int argc, char *argv[])
{
	int ret = acct(argv[1]);
	printf("acct: ret = %d, %s\n", ret, strerror(errno));
	return 0;
}
