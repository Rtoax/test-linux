#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

int sys_pause(void)
{
	return syscall(SYS_pause);
}

int main(int argc, char *argv[])
{
	printf("Pause, wait a signal.\n");
	pause();
	sys_pause();
	return 0;
}
