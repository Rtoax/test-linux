#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <argp.h>

#include "qcow2.h"

static char *qcow2_name;
static int verbose = 0;

const char argp_prog_doc[] =
	"USAGE: [-q <qcow2>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "qcow2", 'q', "QCOW2", 0, "qcow2 name" },
	{ "verbose", 'v', NULL, 1, "Display detail" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'q':
		qcow2_name = arg;
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
	FILE *fp;
	QCowHeader qcowhdr;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (!qcow2_name) {
		fprintf(stderr, "Speicfy qcow2 with -q.\n");
		return -ENOENT;
	}

	fp = fopen(qcow2_name, "r");
	if (!fp) {
		fprintf(stderr, "fopen(%s) %m\n", qcow2_name);
		return -EINVAL;
	}

	fread(&qcowhdr, sizeof(QCowHeader), 1, fp);

	fclose(fp);
	return 0;
}
