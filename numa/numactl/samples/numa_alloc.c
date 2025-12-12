#include <stdio.h>
#include <numa.h>

int main(void)
{
	size_t size = numa_pagesize();
	char *str = numa_alloc(size);
	printf("numa_alloc ret %p\n", str);
	printf("numa_max_node = %d\n", numa_max_node());
	numa_free(str, size);
	return 0;
}
