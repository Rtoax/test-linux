#include <argp.h>
#include <stdbool.h>

const char *interface;
int verbose = false;

const char argp_prog_doc[] =
	"USAGE: [-i <interface>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "interface", 'i', "INTERFACE", 0, "Network interface to attach" },
	{ "verbose", 'v', "VERBOSE", 1, "Display detail" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'i':
		interface = arg;
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

int main(int argc, char **argv)
{
	int err;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (!interface) {
		fprintf(stderr, "Speicfy interface with -i.\n");
		return -ENOENT;
	}

	printf("handle interface %s, verbose %d\n", interface, verbose);

	return 0;
}
