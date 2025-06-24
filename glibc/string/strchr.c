#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char *s_addr, *filename;
	char *str = "/bin/bash:0x00000000000d1c70";
	unsigned long offset;

	printf("%s\n", strchr(str, ':'));

	/**
	 * See kernel trace_uprobe_create()
	 */
	filename = strdup(str);
	s_addr = strrchr(filename, ':');
	*s_addr++ = '\0';
	offset = strtoul(s_addr, NULL, 0);
	printf("%s %s(%lx)\n", filename, s_addr, offset);

	free(filename);
	return 0;
}
