#include <stdio.h>
#include <gperftools/tcmalloc.h>
#include <gperftools/heap-profiler.h>
#include <gperftools/malloc_extension_c.h>

int main(void)
{
	HeapProfilerStart("rtoax");

	char *str = tc_malloc(1024);
	printf("%s\n", str);

	int ret = MallocExtension_VerifyAllMemory();
	printf("%d\n", ret);

	printf("GetHeapProfile() \n %s\n", GetHeapProfile());

	HeapProfilerStop();
	tc_free(str);
}
