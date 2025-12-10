#include <stdio.h>
#include <numa.h>

int main(void)
{
	printf("numa_preferred = %d\n", numa_preferred());
	return 0;
}
