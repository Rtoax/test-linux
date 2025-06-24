#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <sys/ipc.h>
#include <sys/shm.h>


int main(void)
{
#define P(v) printf("%-32s : %d\n", #v, v);
	P(IPC_STAT);
	P(IPC_SET);
	P(IPC_RMID);
	P(IPC_INFO);
	P(SHM_INFO);
	P(SHM_STAT);
	P(SHM_STAT_ANY);
	P(SHM_LOCK);
	P(SHM_UNLOCK);

	return 0;
}
