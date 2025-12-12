#include <stdio.h>
#include <numa.h>

int main(void)
{
	printf("numa_pagesize = %d\n", numa_pagesize());
	return 0;
}

