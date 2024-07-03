#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(void)
{
	int segment_id;
	char* mem;
	struct shmid_ds shmds;
	int segment_size;
	const int shared_segment_size = 0x6400;

	/* Allocate a shared memory segment. */
	segment_id = shmget(IPC_PRIVATE, shared_segment_size,
			    IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

	/* Attach the shared memory segment. */
	mem =(char*)shmat(segment_id, 0, 0);
	printf("shared memory attached at address %p\n", mem);

	/* Determine the segment’s size. */
	shmctl(segment_id, IPC_STAT, &shmds);
	segment_size = shmds.shm_segsz;
	printf("segment size: %d\n", segment_size);

	/* Write a string to the shared memory segment. */
	sprintf(mem, "Hello, world.");

	/* Detach the shared memory segment. */
	shmdt(mem);

	/* Reattach the shared memory segment, at a different address. */
	mem =(char*)shmat(segment_id, (void*)0x5000000, 0);
	printf("shared memory reattached at address %p\n", mem);

	/* Print out the string from shared memory. */
	printf("%s\n", mem);

	/* Detach the shared memory segment. */
	shmdt(mem);

	/* Deallocate the shared memory segment. */
	shmctl(segment_id, IPC_RMID, 0);

	return 0;
}
