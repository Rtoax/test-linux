#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void)
{
	key_t key;
	int shm_id;
	char *p;

	key = ftok("/dev/shm/myshm1", 0);
	shm_id = shmget(key, 0x400000, 0666);
	p = (char*)shmat(shm_id, NULL, 0);

	printf("%c %c %c %c .\n", p[0], p[1], p[2], p[3]);
	shmdt(p);

	return 0;
}
