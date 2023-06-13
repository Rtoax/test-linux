#include <stdio.h>
#include <errno.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>


int main(void)
{
	int ret;

	uid_t uid = getuid();

	printf("getuid = %d\n", uid);

	ret = setuid(uid);
	if (ret != 0) {
		perror("setuid: ");
	}

	return 0;
}
