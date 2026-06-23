// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#include <errno.h>
#include <stdio.h>
#include "file.h"
#include "plot.h"
#ifdef HAVE_JSON_C
#include <json-c/json.h>
#define FILE_JSON "plotcake.json"
#endif

#define FILE_DATA "plotcake.dat"

static int save_txt(const struct plot *p)
{
	int lg_idx;
	char *path = FILE_DATA;
	FILE *fp = fopen(path, "w");
	if (!fp) {
		fprintf(stderr, "ERROR: open %s failed, %m\n", path);
		return -errno;
	}

	fprintf(fp, "#    lgroup title\n");
	fprintf(fp, "plot %d \"%s\" \"%s\" \"%s\"\n", p->lgcount, p->title,
		p->label_x, p->label_y);

	lg_idx = 0;
	for_each_lg(p, lg)
	{
		fprintf(fp, "#      idx nline\n");
		fprintf(fp, "lgroup %d %d\n", lg_idx, lg->count);

		for_each_line(lg, ln)
		{
			fprintf(fp, "#    lgidx lnidx nvals\n");
			fprintf(fp, "line %d %d %ld\n", lg_idx, ln->id,
				ln->count);

			fprintf(fp, "#     lnidx value sec usec\n");
			for_each_value(ln, v)
			{
				fprintf(fp, "value %d %lf %ld %ld\n", ln->id,
					v->v, v->tv.tv_sec, v->tv.tv_usec);
			}
		}

		lg_idx++;
	}

	fclose(fp);
	return 0;
}

#ifdef HAVE_JSON_C
static int save_json(const struct plot *p)
{
	json_object *root, *plot;

	root = json_object_new_object();
	plot = json_object_new_object();

	json_object_object_add(root, "plot", plot);

	json_object_object_add(plot, "title", json_object_new_string(p->title));
	json_object_object_add(plot, "xlabel",
			       json_object_new_string(p->label_x));
	json_object_object_add(plot, "ylabel",
			       json_object_new_string(p->label_y));
	json_object_object_add(plot, "lgcount",
			       json_object_new_int(p->lgcount));

	for_each_lg(p, lg)
	{
		json_object *lgroup = json_object_new_object();
		json_object *lines = json_object_new_object();

		json_object_object_add(plot, "lgroup", lgroup);
		json_object_object_add(lgroup, "lncount",
				       json_object_new_int(lg->count));
		json_object_object_add(lgroup, "lines", lines);

		int lnidx = 0;
		for_each_line(lg, ln)
		{
			char lns[16];
			snprintf(lns, 16, "%d", lnidx);
			json_object *line = json_object_new_object();

			json_object_object_add(lines, lns, line);

			json_object_object_add(line, "vcount",
					       json_object_new_int(ln->count));

			json_object *values = json_object_new_object();
			json_object_object_add(line, "values", values);

			int vidx = 0;
			for_each_value(ln, v)
			{
				char vs[16];
				snprintf(vs, 16, "%d", vidx);
				json_object *value = json_object_new_object();
				json_object_object_add(values, vs, value);

				json_object_object_add(
					value, "v",
					json_object_new_double(v->v));

				json_object *tv = json_object_new_array();
				json_object_array_add(
					tv,
					json_object_new_uint64(v->tv.tv_sec));
				json_object_array_add(
					tv,
					json_object_new_uint64(v->tv.tv_usec));

				json_object_object_add(value, "tv", tv);

				vidx++;
			}
			lnidx++;
		}
	}

	json_object_to_file_ext(FILE_JSON, root, JSON_C_TO_STRING_PRETTY);
	json_object_put(root);
	return 0;
}
#endif

static struct plot_file_operations pf_ops[] = {
	{
		.name = "txt",
		.save = &save_txt,
	},
#ifdef HAVE_JSON_C
	{
		.name = "json",
		.save = &save_json,
	},
#endif
};

/**
 * only have one plot
 */
int save_plot(const struct plot *p)
{
	int err = 0;
	for (int i = 0; i < sizeof(pf_ops) / sizeof(pf_ops[0]); i++) {
		if (!pf_ops[i].save)
			continue;
		fprintf(stderr, "Save to %s\n", pf_ops[i].name);
		err = err ?: pf_ops[i].save(p);
	}
	return err;
}

static void file_create(struct lgroup *lg, void *arg)
{
	// TODO
}

static void file_update(struct lgroup *lg, void *arg)
{
	// TODO
}

static void file_plot_debug(const struct lgroup *lg, void *arg)
{
	// TODO
}

static struct lgroup_operations file_ops = {
	.create = file_create,
	.update = file_update,
	.plot_debug = file_plot_debug,
};

struct lgroup lg_file = {
	.ops = &file_ops,
};
