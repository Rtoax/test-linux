#include <argp.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
#include "file.h"

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

struct version_format {
	const char *seperator;
	const char *major, *minor, *patch;
};

struct json {
	const char *version;
	struct {
		struct {
			char length[16];
			struct {
				const char *argument[16];
			} command;
			struct version_format format;
		} version;
	} common;
};

int json_common(struct json *j, json_object *c)
{
	int len;
	json_object *version, *length, *command, *format;

	json_object_object_get_ex(c, "version", &version);

	json_object_object_get_ex(version, "length", &length);
	assert(json_object_get_type(length) == json_type_array);

	len = json_object_array_length(length);
	for (int i = 0; i < len; i++) {
		json_object *elem = json_object_array_get_idx(length, i);
		assert(json_object_get_type(elem) == json_type_int);

		int val = json_object_get_int(elem);
		j->common.version.length[i] = val;
	}

	json_object_object_get_ex(version, "command", &command);
	json_object *argument;
	json_object_object_get_ex(command, "argument", &argument);
	len = json_object_array_length(argument);
	for (int i = 0; i < len; i++) {
		json_object *elem = json_object_array_get_idx(argument, i);
		assert(json_object_get_type(elem) == json_type_string);

		j->common.version.command.argument[i] =
			json_object_get_string(elem);
	}

	json_object_object_get_ex(version, "format", &format);
	json_object *seperator, *major, *minor, *patch;
	json_object_object_get_ex(format, "seperator", &seperator);
	j->common.version.format.seperator = json_object_get_string(seperator);
	json_object_object_get_ex(format, "major", &major);
	j->common.version.format.major = json_object_get_string(major);
	json_object_object_get_ex(format, "minor", &minor);
	j->common.version.format.minor = json_object_get_string(minor);
	json_object_object_get_ex(format, "patch", &patch);
	j->common.version.format.patch = json_object_get_string(patch);

	return 0;
}

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

	char *content = alloc_buf_read_file(json);
	json_object *root, *version, *common, *software;

	struct json *j = malloc(sizeof(struct json));
	memset(j, 0, sizeof(struct json));

	root = json_tokener_parse(content);

	/* version */
	json_object_object_get_ex(root, "version", &version);
	j->version = json_object_get_string(version);

	/* common */
	json_object_object_get_ex(root, "common", &common);
	json_common(j, common);

	/* software */
	json_object_object_get_ex(root, "software", &software);

	if (verbose) {
		fprintf(stderr, "version %s\n", j->version);
		for (int i = 0; j->common.version.length[i]; i++) {
			fprintf(stderr, "common.version.length[%d] %d\n", i,
				j->common.version.length[i]);
		}
		for (int i = 0; j->common.version.command.argument[i]; i++) {
			fprintf(stderr,
				"common.version.command.argument[%d] %s\n", i,
				j->common.version.command.argument[i]);
		}
		fprintf(stderr, "common.version.format.seperator %s\n",
			j->common.version.format.seperator);
		fprintf(stderr, "common.version.format.major %s\n",
			j->common.version.format.major);
		fprintf(stderr, "common.version.format.minor %s\n",
			j->common.version.format.minor);
		fprintf(stderr, "common.version.format.patch %s\n",
			j->common.version.format.patch);
	}

	free(j);
	free(content);
	return 0;
}
