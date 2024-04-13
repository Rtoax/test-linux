#include <gperftools/tcmalloc.h>
#include <stdio.h>

int main(void)
{
	char *str = tc_malloc(1024);
	printf("%s\n", str);

	int ret = MallocExtension_VerifyAllMemory();
	printf("%d\n", ret);

	ret = MallocExtension_VerifyNewMemory(str);
	printf("%d\n", ret);

	ret = MallocExtension_VerifyNewMemory(NULL);
	printf("%d\n", ret);

	tc_free(str);
}
