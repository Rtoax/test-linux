#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main(void)
{
	char filename[L_tmpnam];

	printf("%s\n", tmpnam(filename));
	printf("%s\n", tmpnam(NULL));
	printf("%s\n", tmpnam_r(filename));

	return 0;
}
