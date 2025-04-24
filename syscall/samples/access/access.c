#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int main(void)
{
	char file[] = "/etc/os-release";

	if (access(file, F_OK) != 0)
		fprintf(stderr, "F_OK %s\n", strerror(errno));
	if (access(file, R_OK) != 0)
		fprintf(stderr, "R_OK %s\n", strerror(errno));
	if (access(file, W_OK) != 0)
		fprintf(stderr, "W_OK %s\n", strerror(errno));
	if (access(file, X_OK) != 0)
		fprintf(stderr, "X_OK %s\n", strerror(errno));
	if (access(file, F_OK | R_OK) != 0)
		fprintf(stderr, "F_OK | W_OK %s\n", strerror(errno));

	return 0;
}
