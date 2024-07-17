#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <syscall.h>

void sys_sync(void)
{
	syscall(SYS_sync);
}

int main(void)
{
	sync();
	return 0;
}
