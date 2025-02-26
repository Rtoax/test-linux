#include <stdio.h>
#include <numa.h>

int main(void)
{
	long ret;
	long long freep = 0;
	long long freep64 = 0;

	ret = numa_node_size(0, &freep);
	printf("numa_node_size : ret = %ld G, freep = %lld G\n",
		ret / 1024 / 1024, freep / 1024 / 1024);

	ret = numa_node_size64(0, &freep64);
	printf("numa_node_size64 : ret = %ld G, freep = %lld G\n",
		ret / 1024 / 1024, freep64 / 1024 / 1024);

	return 0;
}

