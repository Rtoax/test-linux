#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>


#if !defined(__aarch64__)
int sys_open(const char *pathname, int flags, mode_t mode)
{
	return syscall(__NR_open, pathname, flags, mode);
}
#endif

int main(void)
{

	return 0;
}
