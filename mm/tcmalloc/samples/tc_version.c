#include <stdio.h>
#include <gperftools/tcmalloc.h>

int main(void)
{
	int major;
	int minor;
	const char *patch;
	const char *str;

	str = tc_version(&major, &minor, &patch);
	printf("tcmalloc-%d.%d%s patch:%s \n", major, minor, patch, str);

	return 0;
}

