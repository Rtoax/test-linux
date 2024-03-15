#include <stdio.h>
#include <errno.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

int main(void)
{
	int ret;

	uid_t ruid = getuid();
	uid_t euid = geteuid();

	printf("getuid = %d\n", ruid);
	printf("geteuid = %d\n", euid);

	ret = setreuid(ruid, euid);
	if (ret != 0) {
		perror("setreuid: ");
	}

	return 0;
}
