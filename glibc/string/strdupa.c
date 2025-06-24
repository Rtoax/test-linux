/**
 * strdupa(3) use alloca(3) to allocate the buffer on stack.
 */
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
	/* duplicate string on stack */
	char *wr_path = strdupa(path);
	char *cp = strtok(wr_path, ":");

	while (cp != NULL) {
		puts(cp);
		cp = strtok(NULL, ":");
	}
	return 0;
}
