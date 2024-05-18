#include <stdio.h>
#include <numa.h>

int main(void)
{
	long long ret;
	long long freep = 0;

	ret = numa_node_size64(0, &freep);
	printf("numa_node_size64 : ret = %lld G, freep = %lld G\n",
		ret/1024/1024, freep/1024/1024);

	return 0;
}



