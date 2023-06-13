#include <stdio.h>
#include <errno.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>


int main(void)
{
	int ret;

	gid_t egid = getegid();

	printf("getegid = %d\n", egid);

	ret = setegid(egid);
	if (ret != 0) {
		perror("setegid: ");
	}

	return 0;
}
