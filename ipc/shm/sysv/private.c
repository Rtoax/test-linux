#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(void)
{
	int shmid;
	char* mem;
	struct shmid_ds shmds;
	int shm_size;
	const int size = 0x6400;

	/* Allocate a shared memory segment. */
	shmid = shmget(IPC_PRIVATE, size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

	/* Attach the shared memory segment. */
	mem =(char *)shmat(shmid, 0, 0);
	printf("shared memory attached at address %p\n", mem);

	/* Determine the segment’s size. */
	shmctl(shmid, IPC_STAT, &shmds);
	shm_size = shmds.shm_segsz;
	printf("segment size: %d, %x\n", shm_size, shm_size);

	/* Write a string to the shared memory segment. */
	sprintf(mem, "Hello, world.");

	/* Detach the shared memory segment. */
	shmdt(mem);

	/* Reattach the shared memory segment, at a different address. */
	mem =(char*)shmat(shmid, (void*)0x5000000, 0);
	printf("shared memory reattached at address %p\n", mem);

	/* Print out the string from shared memory. */
	printf("%s\n", mem);

	/* Detach the shared memory segment. */
	shmdt(mem);

	/* Deallocate the shared memory segment. */
	shmctl(shmid, IPC_RMID, 0);

	return 0;
}
