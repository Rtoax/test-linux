#include <stdio.h>
#include <numa.h>

int main(void)
{
	printf("numa_available = %d\n", numa_available());
	printf("numa_max_node = %d\n", numa_max_node());
	printf("numa_max_possible_node = %d\n", numa_max_possible_node());
	return 0;
}

