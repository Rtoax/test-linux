#include <stdio.h>
#include <gperftools/tcmalloc.h>
#include <gperftools/heap-profiler.h>

int main(void)
{
	HeapProfilerStart("rtoax");
	HeapProfilerStop();
}
