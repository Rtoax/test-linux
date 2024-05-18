#include <stdio.h>
#include <numa.h>

int main(void)
{
	printf("numa_max_node = %d\n", numa_max_node());
	return 0;
}

