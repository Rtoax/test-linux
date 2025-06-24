#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <link.h>
#include <libgen.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>


static int check_so_cb(struct dl_phdr_info *info, size_t size, void *data)
{
	const char *soname = data;
	int so_used = 0;
	char buff[PATH_MAX];

	strncpy(buff, info->dlpi_name, PATH_MAX - 1);

	if (!strncmp(basename(buff), soname, strlen(soname)))
		so_used = 1;

	return so_used;
}

/* check whether the given library name is in shared object list */
static int has_shared_object(const char *soname)
{
	static int so_used = -1;

	if (so_used != -1)
		return so_used;

	so_used = dl_iterate_phdr(check_so_cb, (void*)soname);

	return so_used;
}

int main(void)
{
	char *lib = "linux-vdso.so.1";

	if (has_shared_object(lib)) {
		printf("has %s.\n", lib);
	}
	return 0;
}
