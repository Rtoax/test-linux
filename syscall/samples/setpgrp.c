#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t grp = getpgrp();
	printf("getpgid = %d\n", grp);
	printf("setpgid = %d\n", setpgrp());

	return 0;
}
