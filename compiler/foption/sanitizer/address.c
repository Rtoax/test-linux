#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

int malloc_overflow(void)
{
	char *a = (char *)malloc(10);
	char *b = (char *)malloc(10);

	(void)b;

	/* Buffer overflow corrupts 'b's metadata */
	/* Writes 20 bytes into a 10-byte buffer */
	memset(a, 0, 20);
	/* May trigger error when 'b' is freed later */
	free(a);

	return 0;
}

int mmap_overflow(void)
{
	size_t size = getpagesize();
	char *mem = (char *)mmap(NULL, size, PROT_READ | PROT_WRITE,
				 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (mem == MAP_FAILED) {
		perror("mmap");
		return -1;
	}

	/* overflow */
	mem[size + 1] = 'a';

	munmap(mem, size);
	return 0;
}

int main(void)
{
	malloc_overflow();
	mmap_overflow();
	return 0;
}
