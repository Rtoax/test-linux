#include <stdio.h>
#include <errno.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>


int main(void)
{
	int ret;

	uid_t euid = geteuid();

	printf("geteuid = %d\n", euid);

	ret = seteuid(euid);
	if (ret != 0) {
		perror("seteuid: ");
	}

	return 0;
}
