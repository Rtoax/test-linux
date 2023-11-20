#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>


int main(void)
{
	char dir[] = "tmpd-access";

	mkdir(dir, 0700);

	if (0 != access(dir, F_OK))
		fprintf(stderr, "F_OK %s\n", strerror(errno));
	if (0 != access(dir, R_OK))
		fprintf(stderr, "R_OK %s\n", strerror(errno));
	if (0 != access(dir, W_OK))
		fprintf(stderr, "W_OK %s\n", strerror(errno));
	if (0 != access(dir, X_OK))
		fprintf(stderr, "X_OK %s\n", strerror(errno));

	rmdir(dir);

	return 0;
}
