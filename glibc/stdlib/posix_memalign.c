#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>

int main(void)
{
	int ret;
	char *str;
	size_t pgsz = getpagesize();

	ret = posix_memalign((void**)&str, 8, pgsz);
	printf("ret = %d, %p\n", ret, str);

	free(str);
	return 0;
}
