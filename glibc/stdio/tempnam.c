#include <stdio.h>
#include <malloc.h>

int main(void)
{
	char *filename;

	filename = tempnam("./", "tmp-");
	printf("%s\n", filename);

	free(filename);
	return 0;
}
