#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#if !defined(__riscv) && !defined(__aarch64__) && !defined(__loongarch64)
int sys_pause(void)
{
	return syscall(SYS_pause);
}
#else
# define sys_pause()
#endif

int main(int argc, char *argv[])
{
	printf("Pause, wait a signal.\n");
	pause();
	sys_pause();
	return 0;
}
