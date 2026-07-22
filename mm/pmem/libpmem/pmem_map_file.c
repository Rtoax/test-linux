#include <stdio.h>
#include <libpmem.h>

/* "/dev/dax0.0" was created by cxl */
#define DAX_DEVICE "/dev/dax0.0"

int main(void)
{
	/* 0: auto size */
	void *pmem = pmem_map_file(DAX_DEVICE, 0, 0, 0666, NULL, NULL);
	if (pmem == NULL) {
		perror("pmem_map_file failed");
		return 1;
	}

	int *data = (int *)pmem;
	printf("Origin data: 0x%x\n", data[0]);
	data[0] = 0xdeadbeef;
	pmem_persist(data, sizeof(int));
	printf("Write data: 0x%x\n", data[0]);

	pmem_unmap(pmem, 0);
	return 0;
}
