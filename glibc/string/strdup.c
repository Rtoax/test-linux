#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <paths.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <ctype.h>
#include <stddef.h>


const char path[] = _PATH_STDPATH;

int main(void)
{
	char *wr_path = strdup(path);
	char *cp = strtok(wr_path, ":");

	while (cp != NULL) {
		puts(cp);
		cp = strtok(NULL, ":");
	}
	return 0;
}
