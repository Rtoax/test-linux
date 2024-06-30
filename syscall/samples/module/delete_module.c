#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <errno.h>


int sys_delete_module(const char *name, unsigned int flags)
{
	return syscall(SYS_delete_module, name, flags);
}

int main(void)
{
	sys_delete_module("mymod", O_NONBLOCK);
	return 0;
}

