#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "mod_helpers.h"

int main(int argc, char *argv[])
{
	int err, fd;
	char *module_file = NULL;
	void *module_image;
	size_t len;
	struct stat statbuf;

	if (argc > 1)
		module_file = argv[1];

	if (!module_file) {
		fprintf(stderr, "Usage: %s <ko>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fd = open(module_file, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Open %s failed. %m\n", module_file);
		exit(EXIT_FAILURE);
	}

	err = fstat(fd, &statbuf);
	if (err == -1) {
		fprintf(stderr, "fstat %s failed, %m\n", module_file);
		goto close_exit;
	}

	len = statbuf.st_size;
#ifdef USE_MMAP
	module_image = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
#else
	module_image = aligned_alloc(getpagesize(), len);
#endif

	printf("Ready %s size %ld, image %p\n", module_file, len, module_image);

	/* load file to memory */
	read(fd, module_image, len);

	err = sys_init_module(module_image, len, NULL);
	if (err) {
		fprintf(stderr, "failed insmod %s, %m\n", module_file);
	}

#ifdef USE_MMAP
	munmap(module_image, len);
#else
	free(module_image);
#endif
close_exit:
	close(fd);
	return err;
}
