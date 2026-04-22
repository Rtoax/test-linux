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

struct version_command {
	const char *argument[16];
};

struct version_format {
	const char *seperator;
	const char *major, *minor, *patch;
};

struct version {
	int length[16];
	struct version_command command;
	struct version_format format;
};

struct software {
	const char *software; /* glibc */
	const char *name; /* GLibc */
	const char *command[16];
	const char *library[16];
	const char *keys[16];
	const char *extension[16];
	struct version version;
};

struct json {
	const char *version;
	struct {
		struct version version;
	} common;
	struct software software[1024];
};

int json_version(json_object *jv, struct version *v)
{
	int len;
	json_object *length, *command, *format;

	len = 0;
	json_object_object_get_ex(jv, "length", &length);
	if (length) {
		assert(json_object_get_type(length) == json_type_array);
		len = json_object_array_length(length);
	}
	for (int i = 0; i < len; i++) {
		json_object *elem = json_object_array_get_idx(length, i);
		assert(json_object_get_type(elem) == json_type_int);

		int val = json_object_get_int(elem);
		v->length[i] = val;
	}

	len = 0;
	json_object_object_get_ex(jv, "command", &command);
	json_object *argument = NULL;
	if (command) {
		json_object_object_get_ex(command, "argument", &argument);
		len = json_object_array_length(argument);
	}
	for (int i = 0; i < len; i++) {
		json_object *elem = json_object_array_get_idx(argument, i);
		assert(json_object_get_type(elem) == json_type_string);

		v->command.argument[i] = json_object_get_string(elem);
	}

	json_object_object_get_ex(jv, "format", &format);
	if (format) {
		json_object *seperator, *major, *minor, *patch;

		json_object_object_get_ex(format, "seperator", &seperator);
		if (seperator)
			v->format.seperator = json_object_get_string(seperator);

		json_object_object_get_ex(format, "major", &major);
		if (major)
			v->format.major = json_object_get_string(major);

		json_object_object_get_ex(format, "minor", &minor);
		if (minor)
			v->format.minor = json_object_get_string(minor);

		json_object_object_get_ex(format, "patch", &patch);
		if (patch)
			v->format.patch = json_object_get_string(patch);
	}

	return 0;
}

void print_version(const char *pfx, struct version *v)
{
	pfx = pfx ?: "";
	for (int i = 0; v->length[i]; i++) {
		fprintf(stderr, "%scommon.version.length[%d] %d\n", pfx, i,
			v->length[i]);
	}
	for (int i = 0; v->command.argument[i]; i++) {
		fprintf(stderr, "%scommon.version.command.argument[%d] %s\n",
			pfx, i, v->command.argument[i]);
	}
	if (v->format.seperator)
		fprintf(stderr, "%scommon.version.format.seperator %s\n", pfx,
			v->format.seperator);
	if (v->format.major)
		fprintf(stderr, "%scommon.version.format.major %s\n", pfx,
			v->format.major);
	if (v->format.minor)
		fprintf(stderr, "%scommon.version.format.minor %s\n", pfx,
			v->format.minor);
	if (v->format.patch)
		fprintf(stderr, "%scommon.version.format.patch %s\n", pfx,
			v->format.patch);
}

int json_common(struct json *j, json_object *c)
{
	json_object *version;
	json_object_object_get_ex(c, "version", &version);
	json_version(version, &j->common.version);
	return 0;
}

int json_software(struct json *j, json_object *s)
{
	int i = 0;
	json_object_object_foreach(s, key, val)
	{
		struct software *sw = &j->software[i];

		json_object *name, *command, *library, *keys, *extension;
		json_object *version;

		json_object_object_get_ex(val, "name", &name);
		sw->software = key;
		sw->name = json_object_get_string(name);

		json_object_object_get_ex(val, "command", &command);
		if (command) {
			int len = json_object_array_length(command);
			for (int j = 0; j < len; j++) {
				json_object *elem =
					json_object_array_get_idx(command, j);
				assert(json_object_get_type(elem) ==
				       json_type_string);

				sw->command[j] = json_object_get_string(elem);
			}
		}

		json_object_object_get_ex(val, "library", &library);
		if (library) {
			int len = json_object_array_length(library);
			for (int j = 0; j < len; j++) {
				json_object *elem =
					json_object_array_get_idx(library, j);
				assert(json_object_get_type(elem) ==
				       json_type_string);

				sw->library[j] = json_object_get_string(elem);
			}
		}

		json_object_object_get_ex(val, "keys", &keys);
		if (keys) {
			int len = json_object_array_length(keys);
			for (int j = 0; j < len; j++) {
				json_object *elem =
					json_object_array_get_idx(keys, j);
				assert(json_object_get_type(elem) ==
				       json_type_string);

				sw->keys[j] = json_object_get_string(elem);
			}
		}

		json_object_object_get_ex(val, "extension", &extension);
		if (extension) {
			int len = json_object_array_length(extension);
			for (int j = 0; j < len; j++) {
				json_object *elem =
					json_object_array_get_idx(extension, j);
				assert(json_object_get_type(elem) ==
				       json_type_string);

				sw->extension[j] = json_object_get_string(elem);
			}
		}

		json_object_object_get_ex(val, "version", &version);
		if (version) {
			json_version(version, &sw->version);
		}

		i++;
	}
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
	json_software(j, software);

	if (verbose) {
		fprintf(stderr, "version %s\n", j->version);

		print_version("j->common.version.", &j->common.version);

		for (int i = 0; j->software[i].software; i++) {
			fprintf(stderr, "software[%d].software %s\n", i,
				j->software[i].software);
			fprintf(stderr, "software[%d].name %s\n", i,
				j->software[i].name);
			for (int k = 0; j->software[i].command[k]; k++) {
				fprintf(stderr, "software[%d].command[%d] %s\n",
					i, k, j->software[i].command[k]);
			}
			for (int k = 0; j->software[i].library[k]; k++) {
				fprintf(stderr, "software[%d].library[%d] %s\n",
					i, k, j->software[i].library[k]);
			}
			for (int k = 0; j->software[i].keys[k]; k++) {
				fprintf(stderr, "software[%d].keys[%d] %s\n", i,
					k, j->software[i].keys[k]);
			}
			for (int k = 0; j->software[i].extension[k]; k++) {
				fprintf(stderr,
					"software[%d].extension[%d] %s\n", i, k,
					j->software[i].extension[k]);
			}
			char buff[64];
			snprintf(buff, 64, "software[%d].version.", i);
			print_version(buff, &j->software[i].version);
		}
	}

	free(j);
	free(content);
	return 0;
}
