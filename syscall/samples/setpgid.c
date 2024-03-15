#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("setpgid = %d\n", setpgid(getpid(), 0));
	return 0;
}

