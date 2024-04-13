#include <stdio.h>
#include <gperftools/tcmalloc.h>
#include <gperftools/stacktrace.h>

int main(void)
{
	char *str = tc_malloc(1024);
	printf("%s\n", str);

	void* result[10];
	int sizes[10];
	int depth = GetStackFrames(result, sizes, 10, 1);

	printf("depth = %d\n", depth);

	tc_free(str);
}

