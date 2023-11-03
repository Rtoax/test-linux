#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/eventfd.h>
#include "utils.h"


int parse_flags(int argc, char *argv[])
{
	int i;
	int flags = EFD_CLOEXEC;

	void usage(void) {
		fprintf(stderr, "%s [--semaphore] [--nonblock]\n", argv[0]);
	}

	usage();

	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "--semaphore"))
			flags |= EFD_SEMAPHORE;
		else if (!strcmp(argv[i], "--nonblock"))
			flags |= EFD_NONBLOCK;
		else {
			fprintf(stderr, "Unknown arg %s\n", argv[i]);
			usage();
			exit(EXIT_FAILURE);
		}
	}

	return flags;
}
