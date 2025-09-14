#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int main(int argc, char *argv[])
{
	int semid;
	key_t key;
	char *filename = "/etc/os-release";

	key = ftok(filename, 0);
	if (key == -1) {
		fprintf(stderr, "ftok failed, %s\n", strerror(errno));
		return -errno;
	}

	semid = semget(key, 1, IPC_CREAT | IPC_EXCL);
	if (semid == -1) {
		fprintf(stderr, "semget failed, %s\n", strerror(errno));
		return -errno;
	}

	semctl(semid, 0, IPC_RMID);

	return 0;
}
