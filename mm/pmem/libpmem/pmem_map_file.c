#include <stdio.h>
#include <libpmem.h>

#define DAX_DEVICE "/dev/dax0.0"
#define MAP_SIZE (1 * 1024 * 1024 * 1024UL)

int main(void)
{
	void *pmem = pmem_map_file(DAX_DEVICE, MAP_SIZE, 0, 0666, NULL, NULL);
	if (pmem == NULL) {
		perror("pmem_map_file failed");
		return 1;
	}

	int *data = (int *)pmem;
	data[0] = 0xdeadbeef;
	pmem_persist(data, sizeof(int));
	printf("Read data: 0x%x\n", data[0]);

	pmem_unmap(pmem, MAP_SIZE);
	return 0;
}
