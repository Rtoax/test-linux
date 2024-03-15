#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	pid_t pid;

	pid = tcgetpgrp(fileno(stdin));

	printf("tcgetpgrp = %d\n", pid);
	tcsetpgrp(fileno(stdin), pid);

	return 0;
}
