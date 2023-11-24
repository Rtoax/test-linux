#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


static int alloc_size;
static char* memory;

void segv_handler(int signal_number)
{
	printf("memory accessed! signal_number(SIGSEGV) = %d\n", signal_number);
	mprotect(memory, alloc_size, PROT_READ | PROT_WRITE);
}

int main(void)
{
	int fd;
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &segv_handler;
	sigaction(SIGSEGV, &sa, NULL);

	alloc_size = getpagesize();
	printf("alloc_size = %d\n", alloc_size);
	fd = open("/dev/zero", O_RDONLY);
#if 1
	memory = mmap(NULL, alloc_size, PROT_WRITE, MAP_PRIVATE, fd, 0);
#else
	memory = malloc(alloc_size);
#endif
	close(fd);
	memory[0] = 0;

	/* Make the memory unwritable. */
	mprotect(memory, alloc_size, PROT_NONE);

	/* Write to the allocated memory region. */
	memory[0] = 1;
	memory[2] = 2;

	/* All done; unmap the memory. */
	printf("all done, memory[0] = %d\n", memory[0]);
	munmap(memory, alloc_size);
	return 0;
}

