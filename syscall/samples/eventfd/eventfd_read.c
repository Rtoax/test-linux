#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/eventfd.h>
#include "utils.h"

int main(int argc, char *argv[])
{
	eventfd_t count;
	int efd;
	int flags;

	flags = parse_flags(argc, argv);
	flags |= EFD_NONBLOCK;

	efd = eventfd(0, flags);

	eventfd_write(efd, 2);
	eventfd_write(efd, 3);
	eventfd_write(efd, 4);

	eventfd_read(efd, &count);
	printf("count = %ld\n", count);
	eventfd_read(efd, &count);
	printf("count = %ld\n", count);
	eventfd_read(efd, &count);
	printf("count = %ld\n", count);
	eventfd_read(efd, &count);
	printf("count = %ld\n", count);

	eventfd_write(efd, -4);
	eventfd_write(efd, -4);
	eventfd_write(efd, 4);

	eventfd_read(efd, &count);
	printf("count = %ld\n", count);
	eventfd_read(efd, &count);
	printf("count = %ld\n", count);
	eventfd_read(efd, &count);
	printf("count = %ld\n", count);
	eventfd_read(efd, &count);
	printf("count = %ld\n", count);

	close(efd);
	return 0;
}
