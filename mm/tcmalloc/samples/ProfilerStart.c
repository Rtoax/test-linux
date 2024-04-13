#include <stdio.h>
#include <gperftools/tcmalloc.h>
#include <gperftools/profiler.h>

int main(void)
{
	ProfilerStart("rtoax");

	char *str = tc_malloc(1024);
	printf("%s\n", str);

	tc_free(str);

	ProfilerFlush();

	ProfilerStop();
}
