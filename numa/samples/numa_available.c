#include <stdio.h>
#include <numa.h>

int main(void)
{
	printf("numa_available = %d\n", numa_available());
	return 0;
}
