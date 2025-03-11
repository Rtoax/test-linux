#include <argp.h>
#include <stdbool.h>
#include <stdlib.h>

const char *interface;
int verbose = false;

struct extra_args {
	int argc;
	char **argv;
};

const char argp_prog_doc[] =
	"USAGE: [-i <interface>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "interface", 'i', "INTERFACE", 0, "Network interface to attach" },
	{ "verbose", 'v', "VERBOSE", 1, "Display detail" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	struct extra_args *extra_args = state->input;

	switch (key) {
	case 'i':
		interface = arg;
		break;
	case 'v':
		verbose = true;
		break;
	case ARGP_KEY_ARG:
		extra_args->argv = realloc(extra_args->argv, (extra_args->argc + 1) * sizeof(char *));
		extra_args->argv[extra_args->argc++] = arg;
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

int main(int argc, char **argv)
{
	int i, err;
	struct extra_args extra_args = {0};

	err = argp_parse(&argp, argc, argv, 0, NULL, &extra_args);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (!interface) {
		fprintf(stderr, "Speicfy interface with -i.\n");
		return -ENOENT;
	}

	printf("handle interface %s, verbose %d\n", interface, verbose);

	for (i = 0; i < extra_args.argc; i++) {
		printf("extra_args.argv[%d] = %s\n", extra_args.argc, extra_args.argv[i]);
	}
	if (extra_args.argc > 0)
		free(extra_args.argv);

	return 0;
}
