#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	syscall(SYS_chmod, argv[0], 0777);

	return 0;
}
