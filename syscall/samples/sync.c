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
