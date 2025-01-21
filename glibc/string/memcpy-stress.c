/**
 * Check with:
 * $ sudo perf top -p $(pidof memcpy-stress)
 */
#include <argp.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <sys/time.h>


static size_t block_size = 256;
static size_t nloop = 10000000;
static int verbose = false;

const char argp_prog_doc[] =
	"USAGE: [-b <block_size>] [-n <nloop>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "block-size", 'b', "BLOCK_SIZE", 0, "block size for each memory copy" },
	{ "nloop", 'n', "NLLOOP", 0, "memory copy times" },
	{ "verbose", 'v', "VERBOSE", 1, "Display detail" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'b':
		block_size = strtoull(arg, NULL, 10);
		break;
	case 'n':
		nloop = strtoull(arg, NULL, 10);
		break;
	case 'v':
		verbose = true;
		break;
	case ARGP_KEY_ARG:
		argp_usage(state);
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

static void *map(size_t msize)
{
	/* Testing memory allocate */
	void *mem = mmap(NULL, msize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (mem == MAP_FAILED) {
		fprintf(stderr, "memory allocate fatal. %s\n", strerror(errno));
		exit(1);
	}
	return mem;
}

static inline unsigned long usecs(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000UL + tv.tv_usec;
}

int main(int argc, char *argv[])
{
	int err;
	size_t test_nloop;
	char *buf1, *buf2;
	unsigned long start, end;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	test_nloop = nloop;

	buf1 = map(8192);
	buf2 = map(8192);

	start = usecs();

	while (test_nloop--)
		memcpy(buf2, buf1, block_size);

	end = usecs();

	printf("Spent %ld us, block_size %ld B, nloop %ld\n", end - start,
		block_size, nloop);

	munmap(buf1, 8192);
	munmap(buf2, 8192);

	return 0;
}
