#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static int alloc_size;
static char *mem;

void segv_handler(int signal_number)
{
	printf("memory accessed! signal_number(SIGSEGV) = %d\n", signal_number);
	mprotect(mem, alloc_size, PROT_READ | PROT_WRITE);
}

int main(void)
{
	int fd, i;
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &segv_handler;
	sigaction(SIGSEGV, &sa, NULL);

	alloc_size = getpagesize();
	printf("alloc_size = %d\n", alloc_size);
	fd = open("/dev/zero", O_RDONLY);

#ifdef ERROR
	/* failed, need to use mmap() */
	mem = malloc(alloc_size);
#else
	mem = mmap(NULL, alloc_size, PROT_WRITE, MAP_PRIVATE, fd, 0);
#endif

	for (i = 0; i < alloc_size; i += getpagesize())
		mem[i] = 'a';

	close(fd);

	printf("%p\n", mem);

	mem[0] = 0;

	/* Make the memory unreadable and unwritable. */
	mprotect(mem, alloc_size, PROT_NONE);

	sleep(4);

	/**
	 * When mprotect is used to remove memory read and write permissions,
	 * does page handling (calling handle_mm_fault()) occur when reading
	 * or writing memory? My current test results show that page handling
	 * is not triggered. So, where is this SIGSEGV triggered?
	 */

#ifdef TEST_READ
	/* Read */
	printf("reading...\n");
	char ch = mem[0];
	(void)ch;
#else
	/* Write to the allocated memory region. */
	printf("writing...\n");
	mem[0] = 1;
#endif

	/* All done; unmap the memory. */
	printf("all done, mem[0] = %d\n", mem[0]);
	munmap(mem, alloc_size);
	return 0;
}
