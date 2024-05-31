#include <stdio.h>
#include <numa.h>

int main(void)
{
	long ret;
#if defined(__sw_64__)
	long long freep = 0;
#define FREEP_FMT	"%lld"
#else
	long freep = 0;
#define FREEP_FMT	"%ld"
#endif

	ret = numa_node_size(0, &freep);
	printf("numa_node_size : ret = %ld G, freep = "FREEP_FMT" G\n",
		ret / 1024 / 1024, freep / 1024 / 1024);

	return 0;
}

