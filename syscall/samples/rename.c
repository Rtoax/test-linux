#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int erename(const char *oldfile, const char *newfile)
{
	int status;
	if ((status = rename(oldfile, newfile)))
		printf("%s: erename: rename failed", __FILE__);
	return status;
}

int main(void)
{
	mkdir("mkdir.out", 0777);
	rename("mkdir.out", "mkmkmkmk.out");
	return 0;
}

