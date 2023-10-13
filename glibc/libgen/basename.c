#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>


const char *get_basename(const char *name)
{
	const char *base = name ? strrchr(name, '/') : name;
	if (base)
		return base + 1;
	return name;
}

int main(int argc, char *argv[])
{
	char path[] = "/a/b/c/d/e/f";
	printf("%s\n", path);
	printf("%s\n", basename(path));
	printf("%s\n", basename(path));
	printf("%s\n", basename(path));
	printf("%s\n", get_basename(path));

	return 0;
}
