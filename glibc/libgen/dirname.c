#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>


int main(const int argc, const char *argv[])
{
	char str[250] = {"a/b/c/d/e/f/j/h/i/j/k"};

	printf("%s: %s\n", str, dirname(str));
	printf("%s: %s\n", str, dirname(str));
	printf("%s: %s\n", str, dirname(str));

	return 0;
}
