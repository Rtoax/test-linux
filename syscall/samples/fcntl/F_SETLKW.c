#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "fcntl_helpers.h"


int main(int argc, char* argv[])
{
	char *file = argv[1] ?: "a.txt";
	int fd;

	printf("opening %s\n", file);
	fd = open(file, O_CREAT | O_WRONLY, 0644);
	if (fd == -1) {
		fprintf(stderr, "open %s %m\n", file);
		exit(1);
	}

	printf("locking\n");
	tl_fwrlock(fd, true);

	printf("locked; hit Enter to unlock... ");
	getchar();

	printf("unlocking\n");
	tl_funlock(fd);

	close(fd);
	return 0;
}
