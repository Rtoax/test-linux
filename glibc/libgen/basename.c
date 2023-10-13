#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

int main(int argc, char *argv[])
{
	char path[] = "/a/b/c/d/e/f";
	printf("%s\n", path);
	printf("%s\n", basename(path));
	printf("%s\n", basename(path));
	printf("%s\n", basename(path));

	return 0;
}
