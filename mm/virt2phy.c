#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * https://www.kernel.org/doc/Documentation/vm/pagemap.txt
 */
static uintptr_t virt_to_phy(void* virt)
{
	off_t ret;
	uintptr_t entry = 0;
	ssize_t rc;
	long pagesize = sysconf(_SC_PAGESIZE);
	int fd = open("/proc/self/pagemap", O_RDONLY);
	assert(fd != -1 && "failed to open /proc/self/pagemap");
	ret = lseek(fd, (uintptr_t)virt / pagesize * sizeof(uintptr_t), SEEK_SET);
	assert(ret != -1 && "lseek error");
	rc = read(fd, &entry, sizeof(entry));
	assert(rc > 0 && "read error");
	assert(entry != 0 && "failed to get physical address (perhaps forgot sudo?)");
	close(fd);

	return (entry & 0x7fffffffffffffULL) * pagesize +
		((uintptr_t)virt) % pagesize;
}

int main(void)
{
	int i;
	printf("%p %p\n", &i, virt_to_phy(&i));
	return 0;
}
