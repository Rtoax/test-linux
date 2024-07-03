#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "config.h"

int main(void)
{
	key_t key;
	int shm_id, flag;
	char *p;

	key = ftok(PATHNAME, PROJ_ID);
	if ((int)key == -1) {
		perror("key");
		exit(0);
	}

	flag = SVSHM_MODE | IPC_CREAT;

	shm_id = shmget(key, 0x400000, flag);
	if (shm_id == -1) {
		perror("shmget");
		exit(0);
	}

	p = (char *)shmat(shm_id, NULL, 0);
	if (p == (void *)-1) {
		perror("shmat");
		exit(0);
	}

	memset(p, 'A', 0x400000);
	shmdt(p);

	/* Can't IPC_RMID here */
	//shmctl(shm_id, IPC_RMID, 0);

	return 0;
}
