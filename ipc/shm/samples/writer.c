#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void)
{
	key_t key = ftok("/dev/shm/myshm1", 0);
	int shm_id = shmget(key, 0x400000, IPC_CREAT | 0666);
	char *p = (char*)shmat(shm_id, NULL, 0);

	memset(p, 'A', 0x400000);
	shmdt(p);

	return 0;
}
