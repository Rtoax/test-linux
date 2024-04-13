#include <stdio.h>
#include <gperftools/tcmalloc.h>
#include <gperftools/heap-profiler.h>

int main(void)
{
	HeapProfilerStart("rtoax");

	char *str = tc_malloc(1024);
	printf("%s\n", str);

	int ret = MallocExtension_VerifyAllMemory();
	printf("%d\n", ret);

	ret = IsHeapProfilerRunning();
	printf("%d\n", ret);

	tc_free(str);

}
