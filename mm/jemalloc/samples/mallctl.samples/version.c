#include <stdio.h>
#include <jemalloc/jemalloc.h>

void get_jemalloc_version(char *version, size_t *ver_len)
{
	//Return the jemalloc version string.
	mallctl("version", version, ver_len, NULL, 0);
}

int main(int argc,char **argv)
{
	char version[256];
	size_t ver_len = 256;

	get_jemalloc_version(version, &ver_len);

	printf("Version: %s, %ld.\n", version, &ver_len);

	return 0;
}

