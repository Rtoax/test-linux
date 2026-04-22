#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <json-c/json.h>

static char *json = NULL;
static bool verbose = false;

const char argp_prog_doc[] = "USAGE: [-j <JSON>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "json", 'j', "JSON", 0, "Input json config file" },
	{ "verbose", 'v', NULL, 1, "Display detail" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'j':
		json = arg;
		break;
	case 'v':
		verbose = true;
		break;
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
	int err;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}
	if (!json) {
		fprintf(stderr, "Must specify json file with -j.\n");
		return -ENOENT;
	}

	return 0;
}
