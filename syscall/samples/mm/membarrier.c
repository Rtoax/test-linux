#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/syscall.h>
#include <linux/membarrier.h>

int main(void)
{
/* FIXME */
#ifdef MEMBARRIER_CMD_FLAG_CPU
	syscall(SYS_membarrier, MEMBARRIER_CMD_GLOBAL, MEMBARRIER_CMD_FLAG_CPU,
		0);
#endif

	return 0;
}
