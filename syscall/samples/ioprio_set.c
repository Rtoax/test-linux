#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

int main(void)
{
	int which;
	int who;
	int ret;

	/* TODO */
	which = who = 0;

	ret = syscall(SYS_ioprio_set, which, who);
	printf("0x%x\n", ret);

	return 0;
}


