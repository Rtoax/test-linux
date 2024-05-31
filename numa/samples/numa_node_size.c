#include <stdio.h>
#include <numa.h>

int main(void)
{
	long ret;
	long long freep = 0;

	ret = numa_node_size(0, &freep);
	printf("numa_node_size : ret = %ld G, freep = %lld G\n",
		ret / 1024 / 1024, freep / 1024 / 1024);

	return 0;
}

