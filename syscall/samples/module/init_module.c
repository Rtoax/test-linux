#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <linux/module.h>    /* Definition of MODULE_* constants */

#include "mod_helpers.h"

char *module_file = NULL;
int verbose = false;
#ifdef TEST_FINIT_MODULE /* finit_module(2) */
bool force_vermagic = false;
bool force_modversion = false;
#endif

const char argp_prog_doc[] =
	"USAGE: [-i <module file>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "input", 'i', "INPUT", 0, "Input kernel module file" },
#ifdef TEST_FINIT_MODULE /* finit_module(2) */
	/* see modprobe(8) */
	{ "force-vermagic", 'V', NULL, 1, "Skip version magic check" },
	{ "force-modversion", 'M', NULL, 1, "Skip modversion check" },
	{ "force", 'f', NULL, 1, "Skip version magic and modversion check" },
#endif
	{ "verbose", 'v', "VERBOSE", 1, "Display detail" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'i':
		module_file = arg;
		break;
	case 'v':
		verbose = true;
		break;
#ifdef TEST_FINIT_MODULE /* finit_module(2) */
	case 'V':
		force_vermagic = true;
		break;
	case 'M':
		force_modversion = true;
		break;
	case 'f':
		force_vermagic = true;
		force_modversion = true;
		break;
#endif
	case ARGP_KEY_ARG:
		break;
	case ARGP_KEY_END:
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static const struct argp argp = {
	.options = opts,
	.parser = parse_arg,
	.doc = argp_prog_doc,
};

int main(int argc, char *argv[])
{
	int err, fd;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (!module_file) {
		fprintf(stderr, "Must specify kernel module file\n");
		exit(EXIT_FAILURE);
	}

	fd = open(module_file, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Open %s failed. %m\n", module_file);
		exit(EXIT_FAILURE);
	}

#ifdef TEST_FINIT_MODULE /* finit_module(2) */
	int flags = 0;

	if (force_vermagic)
		flags |= MODULE_INIT_IGNORE_VERMAGIC;
	if (force_modversion)
		flags |= MODULE_INIT_IGNORE_MODVERSIONS;

	err = sys_finit_module(fd, "", flags);
	if (err) {
		fprintf(stderr, "failed insmod %s, %m\n", module_file);
	}

#else /* init_module(2) */

	struct stat statbuf;
	void *module_image;
	size_t len;

	err = fstat(fd, &statbuf);
	if (err == -1) {
		fprintf(stderr, "fstat %s failed, %m\n", module_file);
		goto close_exit;
	}

	len = statbuf.st_size;
# ifdef USE_MMAP
	module_image = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
# else
	module_image = aligned_alloc(getpagesize(), len);
# endif

	if (verbose)
		printf("Ready %s size %ld, image %p\n", module_file, len, module_image);

	/* load file to memory */
	read(fd, module_image, len);

	err = sys_init_module(module_image, len, "");
	if (err) {
		fprintf(stderr, "failed insmod %s, %m\n", module_file);
	}

# ifdef USE_MMAP
	munmap(module_image, len);
# else
	free(module_image);
# endif
close_exit:
#endif
	close(fd);
	return err;
}
