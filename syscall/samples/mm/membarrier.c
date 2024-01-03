#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/syscall.h>
#include <linux/membarrier.h>

int main(void)
{
	syscall(SYS_membarrier, MEMBARRIER_CMD_GLOBAL, MEMBARRIER_CMD_FLAG_CPU,
		0);

	return 0;
}
