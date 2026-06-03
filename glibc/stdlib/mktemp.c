#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char path[] = "tmp-XXXXXX";
	char *tmp = mktemp(path);
	printf("tmp = %s\n", tmp ?: "NULL");
	unlink(tmp);
	return 0;
}
