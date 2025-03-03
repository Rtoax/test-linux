/* Copyright (C) 2025 CESTC, Co. All rights reserved. */
/* 2025-02-08	Rong Tao	Create this */
#pragma once

#define __unused __attribute__((unused))

static __unused void proc_display_maps(FILE *out, char *pfx)
{
	char *line = NULL;
	size_t len = 0;
	FILE *fp;

	if (!out)
		out = stdout;

	if (!pfx)
		pfx = "";

	fp = fopen("/proc/self/maps", "r");
	if (!fp) {
		perror("fopen");
		return;
	}

	while (getline(&line, &len, fp) != -1)
		fprintf(out, "%s%s", pfx, line);
	free(line);
}
