#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

int main(int argc, char *argv[])
{
#if !defined(__aarch64__) && !defined(__riscv) && !defined(__loongarch64)
	syscall(SYS_chmod, argv[0], 0777);
#endif

	return 0;
}
