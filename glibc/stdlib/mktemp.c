#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
	char path[] = "tmpd-XXXXXX";
	char *tmp = mktemp(path);
	printf("tmpd = %s\n", tmp ?: "NULL");

	unlink(tmp);
	return 0;
}
