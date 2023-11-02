#include <stdio.h>
#include <unistd.h>
#include <selinux/selinux.h>


int main(void)
{
	char *context;
	pid_t pid = getpid();

	getpidcon(pid, &context);
	printf("%s\n", context);

	freecon(context);
	return 0;
}
