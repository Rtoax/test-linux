#include <gperftools/tcmalloc.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[])
{
	int ret = mallopt(M_CHECK_ACTION, 3);
	printf("mallopt ret = %d\n", ret);

	const char *src = "mcheck test";
	char *ptr = (char *)tc_malloc(sizeof(char) * 32);

	printf("tc_malloc_size = %ld\n", tc_malloc_size(ptr));

	memcpy(ptr, src, strlen(src));
	ptr[32] = '\0'; /* overflow */
	printf("*ptr=%s\n", ptr);

	tc_free(ptr);
	ptr = NULL;
	printf("process end\n");

	return 0;
}

