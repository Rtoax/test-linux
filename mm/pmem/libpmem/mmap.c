#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

/* "/dev/dax0.0" was created by cxl */
#define DAX_DEVICE "/dev/dax0.0"
#define MAP_SIZE (1 * 1024 * 1024 * 1024UL)

int main(void)
{
	int fd = open(DAX_DEVICE, O_RDWR);
	if (fd < 0) {
		perror("Failed to open DAX device");
		return 1;
	}

	void *addr =
		mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED) {
		perror("mmap failed");
		close(fd);
		return 1;
	}

	int *data = (int *)addr;
	printf("Origin data: 0x%x\n", data[0]);
	data[0] = 0x12345678;
	printf("Write data: 0x%x\n", data[0]);

	munmap(addr, MAP_SIZE);
	close(fd);
	return 0;
}
