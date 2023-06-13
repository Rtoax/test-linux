#include <stdio.h>
#include <errno.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>


int main(void)
{
	int ret;

	gid_t gid = getgid();

	printf("getgid = %d\n", gid);

	ret = setgid(gid);
	if (ret != 0) {
		perror("setgid: ");
	}

	return 0;
}
