#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/eventfd.h>


int main(int argc, char *argv[])
{
	eventfd_t count;
	int efd;
	int flags = EFD_NONBLOCK | EFD_CLOEXEC;

	fprintf(stderr, "%s [--semaphore]\n", argv[0]);
	if (argc >= 2 && !strcmp(argv[1], "--semaphore")) {
		flags |= EFD_SEMAPHORE;
	}

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
