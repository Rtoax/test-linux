#include <unistd.h>
#include <stdio.h>

int main(void)
{
	pid_t pid = getpid();

	printf("pid = %d\n", pid);

	return 0;
}
