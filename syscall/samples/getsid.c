#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
	printf("setsid = %d\n", setsid());
	printf("getsid = %d\n", getsid(getpid()));

	return 0;
}
