#include <argp.h>
#include <stdbool.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>


size_t mem_size = 0;
int verbose = false;

const char argp_prog_doc[] =
	"USAGE: [-s <size>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "size", 's', "INTERFACE", 0, "only allocate size of memory, instead of oom" },
	{ "verbose", 'v', "VERBOSE", 1, "display detail" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 's':
		mem_size = strtoul(arg, NULL, 10);
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

void hold_mem(size_t size)
{
	size_t i;
	const int pagesize = getpagesize();
	char *mem;

	if (verbose)
		fprintf(stderr, "Hold %ld B (%ldMib) of memory\n", size,
			size / 1024 / 1024);

	mem = malloc(size);

	while (1) {
		for (i = 0; i < size; i += pagesize)
			mem[i] = 'a';
		sleep(1);
	}
}

void oom(void)
{
	int i;
	const int pagesize = getpagesize();
	const int blk = pagesize * 10;
	char *mem;

	if (verbose)
		fprintf(stderr, "OOMing...\n");

	while (1) {
		mem = malloc(blk);
		for (i = 0; i < blk; i += pagesize)
			mem[i] = 'a';
		/* No need to free(), just leak it. */
	}
}

int main(int argc, char *argv[])
{
	int err;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (mem_size)
		hold_mem(mem_size);
	else
		oom();

	return 0;
}
