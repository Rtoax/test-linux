#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#include "mod_helpers.h"

int main(int argc, char *argv[])
{
	int err;
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

	if (access(module_file, F_OK | R_OK) != 0) {
		fprintf(stderr, "file %s access failed %m\n", module_file);
		exit(EXIT_FAILURE);
	}

	stat(module_file, &statbuf);

	len = statbuf.st_size;

	module_image = aligned_alloc(getpagesize(), len);

	/* load file to memory */
	{
		FILE *fp = fopen(module_file, "r");
		fread(module_image, len, 1, fp);
		fclose(fp);
	}

	err = sys_init_module(module_image, len, NULL);
	if (err) {
		fprintf(stderr, "failed insmod %s, %m\n", module_file);
	}

	free(module_image);
	return err;
}
