#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char path[] = "tmpd-XXXXXX";
	char *tmpd = mkdtemp(path);
	printf("tmpd = %s\n", tmpd ?: "NULL");
	rmdir(tmpd);
	return 0;
}
