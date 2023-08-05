#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>


int main(void)
{
	char dir[] = "tmpd-access";

	mkdir(dir, 0700);

	if (0 != access(dir, F_OK)) {
		perror("access");
	}

	rmdir(dir);

	return 0;
}
