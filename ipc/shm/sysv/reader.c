#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "config.h"

int main(void)
{
	key_t key;
	int shm_id;
	char *p;

	key = ftok(PATHNAME, PROJ_ID);
	if ((int)key == -1) {
		perror("key");
		exit(0);
	}

	shm_id = shmget(key, 0x400000, 0666);
	if (shm_id == -1) {
		perror("shmget");
		exit(0);
	}

	p = (char *)shmat(shm_id, NULL, 0);
	if (p == (void *)-1) {
		perror("shmat");
		exit(0);
	}

	printf("%c %c %c %c .\n", p[0], p[1], p[2], p[3]);
	shmdt(p);

	shmctl(shm_id, IPC_RMID, 0);

	return 0;
}
